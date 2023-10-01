-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';

-- | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
-- | Littering took place at 16:36. No known witnesses.


SELECT * FROM bakery_security_logs WHERE day = 28 AND

-- select interviews on 07/28
SELECT * FROM interviews WHERE month = 7 AND day = 28


-- the thief left the bakery within 10 minutes of the crime, withdrew money in the morning, and called the accomplice < a minute as he/she was leaving the bakery, and flew out of Fiftyville on 28th of July

SELECT name FROM people WHERE license_plate IN
    -- left the bakery within 10 minutes
    (SELECT license_plate
    FROM bakery_security_logs
    WHERE hour = 10 AND minute > 15 AND minute < 25 AND activity = "exit")
    -- withdrew money form atm
    AND id IN
    (SELECT person_id FROM bank_accounts
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE month = 7 AND day = 28 AND transaction_type = "withdraw")
    -- Caller phone-number: the main thief
    AND phone_number IN
    (SELECT caller
    FROM phone_calls
    WHERE month = 7 AND day = 28 AND duration < 60)
    -- Flight detail
    AND passport_number IN
    (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id IN
    (SELECT id FROM airports WHERE city = "Fiftyville") AND year = 2021 AND month = 7 AND day = 29 AND
    -- earliest Fiftyville flight on 29
    hour IN (SELECT MIN(hour) FROM (SELECT hour FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville") AND year = 2021 AND month = 7 AND day = 29))))


-- City escaped to
SELECT * FROM airports
    JOIN flights ON airports.id = flights.destination_airport_id
    WHERE hour IN (SELECT MIN(hour) FROM (SELECT hour FROM flights WHERE origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville") AND year = 2021 AND month = 7 AND day = 29))
    AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville") AND year = 2021 AND month = 7 AND day = 29

-- Accomplice
SELECT name FROM people WHERE phone_number IN
    (SELECT receiver FROM phone_calls WHERE caller IN
    (SELECT phone_number FROM people WHERE name = "Bruce") AND day = 28 AND month = 7 AND duration < 60)