SELECT movies.year, title
FROM movies
WHERE title LIKE 'Harry Potter %'
ORDER BY movies.year