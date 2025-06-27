# SNHU-CS-300-Project-One-Connor-Camire-

For this assignment I was given a CSV file with information on classes and their prerequisites. I took the information and placed it into a hash table. To allow for a fast search through each of the classes. To find the requested class prerequisites, assuming they have any. The CSV file had the format of CSCI300,Introduction to Algorithms,CSCI200,MATH201. CSCI300 being the class,Introduction to Algorithms being the classes name, and lastly both CSCI200 and MATH201 are the classes prerequisites, file is separated by commas.

A roadblock occurred when I needed to order the information from the CSV file. Since hash tables are unable to be organized, I need to take the information moved to the hash table and move it again to a vector list. This allows me to sort the information in the vector in order to display each of the classes in alphanumeric order.

This project and the assignments that led up to it gave me a better overview of different Sorting Algorithms. and how to implement and utilize each, along with each of their strengths and weaknesses. such as hash tables allowing for very fast and efficient searching, but being limited in your ability to organize the information
