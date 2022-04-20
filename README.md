# Global-Music-Chart-Connector
Mira Saldanha and Priyal Patel
C++14

this program reads in data from spotify charts for different countries, and allows the user to see how related different countries are in terms of song overlap. uses hash tables (separate chaining) and a weighted, undirected graph in c++. program also compares our hash table implementation to c++ stl unordered set.

more specifically, program reads in data and stores title, artist, and region for each (region is country). uses c++ std library map to store each country as a key, and hash tables and their values. our hash tables are implemented as arrays of std sets of strings ( set[] ), where each entry is "title artist" to ensure that all different songs with the same name aren't counted only once. the hash function is string length % capacity of the table, so each entry is a set of "title artists" entries of the same mod value. the stl unordered set stores the same entries.

this map is then used to create a weighted undirected graph with an adjacency list implementation. the graph is a std map, with country names as the keys, and a std vector of pair<string, int> as the value. each pair is an adjacent edge, where the string is the country and the int is our calculated weight. weight is calculated by comapring the hash tables for each country and counting the number of overlapping songs.

user decides which hash table implementation is used when program starts. the time it takes to load all data and make the graph is printed.

user can see all countries that the program has data for, see the 5 "most-related" countries to a particular country, see all related countries to a particular country, or see if two countries are related and by how many songs.

data came from https://www.kaggle.com/datasets/dhruvildave/spotify-charts

the dataset we took in had ~700,000 data points (Original.csv). our project had a minimin requirement of 100,000, so we reduced our input to ~106,000 points to make it easier to run on our laptops. we parsed the original dataset first, and then wrote only some of it to another file, and then reduced it more. the resulting csv is what we use in our main src code (Charts.csv). our file is included, but project can be expanded to use more of original dataset if a new csv is created with our parsing code. should also be noted that original data contains some inconsistent use of double quotes and commas in some song titles or artist names, which are taken care of in parsing. data also contains some "bad" data points where the "region" listed is something other than a country. we deleted them manually because it was easier, given the set we were working with, but parsing file can probably be adjusted to take care of that if desired.
