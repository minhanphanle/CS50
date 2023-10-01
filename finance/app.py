import os
import datetime
import pytz
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from string import (ascii_uppercase, ascii_lowercase, whitespace, digits)

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
    id = session["user_id"]
    port_data = db.execute("SELECT * FROM stocks WHERE user_id = ?", id)

    count = db.execute("SELECT COUNT(*) FROM stocks WHERE user_id = ?", id)[0]["COUNT(*)"]

    total_sval = 0

    # calculate current portfolio

    for i in range(count):
        total_sval += port_data[i]["total"]

    cash = db.execute("SELECT cash from users WHERE id = ?", id)[0]["cash"]
    return render_template("index.html", data=port_data, cash=usd(cash), total=usd(total_sval + cash))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = (request.form.get("shares"))
        if shares.isdecimal():
            shares = int(shares)
        else:
            return apology("Invalid shares")
        symbol_l = lookup(symbol)
        id = session["user_id"]
        balance = db.execute("SELECT cash FROM users WHERE id = ?", id)[0]["cash"]


        if (not symbol) or (not shares):
            return apology("Must enter all fields")
        elif not symbol_l:
            return apology("Invalid symbol")
        elif shares <= 0:
            return apology("Shares must be larger than 0")
        else:
            total_price = symbol_l["price"] * shares
            if balance > total_price:
                time = datetime.datetime.now(pytz.timezone("US/Eastern"))
                new_balance = balance - total_price
                s = symbol_l["symbol"]


                db.execute("INSERT INTO transactions (user_id, type, symbol, shares, total, time) VALUES(?, ?, ?, ?, ?, ?)", id, "buy", symbol, shares,total_price, time)

                db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, id)

                s_existed = db.execute("SELECT * FROM stocks WHERE user_id = ? AND symbol = ?", id, s)
                if s_existed:
                    db.execute("UPDATE stocks SET quantity = quantity + ?, total = total + ? WHERE user_id = ? AND symbol = ?", shares, total_price, id, s)
                else:
                    db.execute("INSERT INTO stocks (user_id, symbol, quantity, total) VALUES(?, ?, ?, ?)", id, s, shares, total_price)

                return index()
            else:
                return apology("Balance not enough.")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    id = session["user_id"]
    trans_data = db.execute("SELECT * FROM transactions WHERE user_id = ?", id)

    return render_template("history.html", data = trans_data)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
        symbol = request.form.get("symbol")

        if symbol:
            symbol_searched = lookup(symbol)
            if symbol_searched:
                return render_template("quoted.html", stock_name=symbol_searched["name"], stock_price=usd(symbol_searched["price"]))
            else:
                return apology("Invalid symbol")
        else:
            return apology("Please enter a symbol")
    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        name = request.form.get("username")
        pw = request.form.get("password")
        cf = request.form.get("confirmation")
        special_char = ['$', '%', '#', '*']

        if (not name) or (not pw) or (not cf):
            return apology("Please input all fields")
        elif pw != cf:
            return apology("Password did not match")
        # elif len(pw) < 6:
        #     return apology("Password must be at least 6 characters!")
        # elif len(pw) > 18:
        #     return apology("Password must be at most 18 characters!")
        # elif not any(c in special_char for c in pw):
        #     return apology("Password must contain at least 1 special character: '$', '%', '#', '*'")
        # elif not any(c.isupper() for c in pw):
        #     return apology("Password must contain at least 1 uppercase character")
        else:
            for i in db.execute("SELECT username FROM users"):
                if name == i["username"]:
                    return apology("Duplicate username!")
            hash = generate_password_hash(pw)
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", name, hash)
            return render_template("login.html")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    # """Sell shares of stock"""
    id = session["user_id"]
    stocks = db.execute("SELECT symbol FROM stocks WHERE user_id = ?", id)
    stock_list = []
    for i in stocks:
        stock_list.append(i["symbol"])
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        symbol_l = lookup(symbol)
        s = symbol_l["symbol"]

        balance = db.execute("SELECT cash FROM users WHERE id = ?", id)[0]["cash"]


        # port_data = db.execute("SELECT * FROM stocks WHERE user_id = ?", id)

        # count = db.execute("SELECT COUNT(*) FROM stocks WHERE user_id = ?", id)[0]["COUNT(*)"]

        s_existed = db.execute("SELECT * FROM stocks WHERE user_id = ? AND symbol = ?", id, s)

        if (not symbol) or (not shares):
            return apology("Must enter all fields")
        elif not symbol_l or not s_existed:
            return apology("Invalid symbol")
        elif (s_existed[0]["quantity"] < shares):
            return apology("Not enough shares to sell")
        else:
            total_price = symbol_l["price"] * shares
            old_quantity = s_existed[0]["quantity"]
            new_quantity = old_quantity - shares
            new_total_value = new_quantity * symbol_l["price"]

            time = datetime.datetime.now(pytz.timezone("US/Eastern"))
            new_balance = balance + total_price

            db.execute("INSERT INTO transactions (user_id, type, symbol, shares, total, time) VALUES(?, ?, ?, ?, ?, ?)", id, "sell", symbol, shares, total_price, time)

            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, id)

            if new_quantity == 0:
                db.execute("DELETE FROM stocks WHERE user_id = ? AND symbol = ?", id, s)
            else:
                db.execute("UPDATE stocks SET quantity = ?, total = ? WHERE user_id = ? AND symbol = ?", new_quantity, new_total_value, id, s)

            return index()
    else:
        return render_template("sell.html", symbols=stock_list)