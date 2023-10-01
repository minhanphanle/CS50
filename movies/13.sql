SELECT DISTINCT name
FROM people
    JOIN stars on people.id = stars.person_id
    WHERE movie_id IN (
        SELECT movie_id
        FROM stars
            JOIN people on people.id = stars.person_id
        WHERE people.name = 'Kevin Bacon' AND
        people.birth = 1958
    )
AND people.name != 'Kevin Bacon'