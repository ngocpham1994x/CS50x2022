import os, datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = int(session["user_id"])

    row_purchases = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares, SUM(total_price) as total_price FROM purchases WHERE user_id = ? GROUP BY symbol;",
        user_id,
    )
    row_users = db.execute("SELECT username, cash FROM users WHERE id = ?", user_id)
    grand_total = row_users[0]["cash"]  # initialize the grand_total

    for row in row_purchases:
        info = lookup(row["symbol"])
        value = info["price"] * row["total_shares"]
        row["unit_price"] = info["price"]
        row["total_price"] = row["total_price"]
        row["value"] = value
        grand_total += value

    user = {}
    user["username"] = row_users[0]["username"]
    user["balance"] = row_users[0]["cash"]
    user["grand_total"] = grand_total
    user["purchases"] = row_purchases
    print(user)

    return render_template("index.html", user=user, stocks=user["purchases"])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    user_id = int(session["user_id"])

    if request.method == "POST":
        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Get stock info from lookup function
        info = lookup(symbol)

        if not symbol:
            return apology("must provide stock symbol", 400)

        # If no stock info was returned, show an apology
        if not info:
            return apology("invalid stock symbol", 400)

        try:
            if not shares or int(shares) <= 0:
                return apology("must provide positive number of shares", 400)
        except ValueError:
            # If conversion to int fails, it means shares is not a valid integer
            return apology("must provide a valid integer number of shares", 400)

        curr_datetime = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")
        price = info["price"] * int(shares)
        row_users = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = row_users[0]["cash"]
        if cash > price:
            balance = float(cash) - float(price)
            # Update a value in a specific cell
            db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, user_id)
            db.execute(
                "INSERT INTO purchases VALUES(?, ?, ?, ?, ?, ?)",
                curr_datetime,
                user_id,
                symbol,
                int(shares),
                info["price"],
                price,
            )

        else:
            return apology("not enough cash", 400)

        # Render the quoted.html template with stock info
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    user_id = int(session["user_id"])

    row_purchases = db.execute("SELECT * FROM purchases WHERE user_id = ?", user_id)
    row_users = db.execute("SELECT username, cash FROM users WHERE id = ?", user_id)
    total = db.execute(
        "SELECT SUM(total_price) as total FROM purchases WHERE user_id = ?", user_id
    )

    if row_purchases:
        for row in row_purchases:
            row["unit_price"] = row["unit_price"]
            row["total_price"] = row["total_price"]

        user = {}
        user["username"] = row_users[0]["username"]
        user["purchases"] = row_purchases
        user["total"] = total[0]["total"]
        #print(user)

        return render_template("history.html", user=user, stocks=user["purchases"])

    else:
        return redirect("/")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide stock symbol", 400)

        # Get stock info from lookup function
        info = lookup(symbol)

        # If no stock info was returned, show an apology
        if not info:
            return apology("invalid stock symbol", 400)

        # Render the quoted.html template with stock info
        return render_template("quoted.html", stock=info)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        # Validate username
        username = request.form.get("username")

        try:
            # Querying the database to see if the id exists
            result = db.execute("SELECT * FROM users WHERE username = ?", username)

            if result:
                return apology("Username exists. Pick another username.", 400)

        except Exception as e:
            return apology(e)

        # Validate password
        password = request.form.get("password")
        password_hash = generate_password_hash(password)
        confirmation = request.form.get("confirmation")

        if not username or not password or not confirmation:
            return apology("Username or Password or Confirmation is blank", 400)
        elif confirmation != password:
            return apology("Password and Confirmation are not matched", 400)

        # Remember registrant
        db.execute(
            "INSERT INTO users (username, hash) VALUES(?, ?)", username, password_hash
        )
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = int(session["user_id"])

    stocks = db.execute(
        "SELECT symbol FROM purchases WHERE user_id = ? GROUP BY symbol;",
        user_id,
    )

    if request.method == "POST":
        # Ensure symbol was submitted
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Get stock info
        row = db.execute(
            "SELECT symbol, SUM(shares) AS total_shares, SUM(total_price) as total_price FROM purchases WHERE user_id = ? AND symbol = ? GROUP BY symbol;",
            user_id,
            symbol,
        )
        info = lookup(symbol)

        # If no stock info was returned, show an apology
        if not symbol:
            return apology("must provide stock symbol", 400)

        # If no shares info was returned, show an apology
        try:
            if not shares or int(shares) <= 0:
                return apology("must provide positive number of shares", 400)
        except ValueError:
            # If conversion to int fails, it means shares is not a valid integer
            return apology("must provide a valid integer number of shares", 400)

        if not row or row[0]["total_shares"] <= 0:
            return apology("user does not own this stock", 400)
        elif int(shares) > row[0]["total_shares"]:
            return apology("user tries to sell more stocks than what they own", 400)
        else:
            curr_datetime = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")
            price = info["price"] * int(shares)
            row_users = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
            cash = row_users[0]["cash"]
            balance = float(cash) + float(price)

            # Update a value in a specific cell
            db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, user_id)
            db.execute(
                "INSERT INTO purchases VALUES(?, ?, ?, ?, ?, ?)",
                curr_datetime,
                user_id,
                symbol,
                -int(shares),
                info["price"],
                -price,
            )

            # Render the quoted.html template with stock info
            return redirect("/")

    else:
        return render_template("sell.html", stocks=stocks)


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    """Add more cash."""

    user_id = int(session["user_id"])
    row_users = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = row_users[0]["cash"]

    if request.method == "POST":
        # Ensure cash was submitted
        added_cash = request.form.get("cash")
        if not added_cash or int(added_cash) <= 0:
            return apology("no cash added", 400)

        balance = float(cash) + float(int(added_cash))

        # update new cash
        db.execute("UPDATE users SET cash = ? WHERE id = ?", balance, user_id)

        # Render
        return redirect("/add")

    else:
        return render_template("add.html", cash=usd(row_users[0]["cash"]))
