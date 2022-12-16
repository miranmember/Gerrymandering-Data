# Gerrymandering-Data
This is a C++ program that reads in information from two files: "districts.txt" and "eligible_voters.txt". The program allows the user to search for a state by name and displays the number of eligible voters who did not vote in that state. The program also includes a message to encourage the user to vote. The program uses structs to store information about districts and voters, and a custom vector class called "ourvector" to store information about districts for each state. The program includes several functions to manipulate the data, including "toUpper" which converts a string to uppercase, "getName" which extracts the name from a line of text, "getDistrict" which extracts district information from a line of text and counts the number of districts, and "getVotes" which stores district information in a vector.

# How To Use
After building the code, Use the 'load' command to load in district data, voters data.
There are district and voters files to use as an example.
Use the 'search' to search for a specific state/district.
After loading in the data and searching for a state, Use the 'stats',
'plot' or 'participant' command to look up more information for that state/district.
