Field Stripper

Tabulates sequential, fixed length, undeliminated entries in a text file.
The first time FieldStripper starts up it will load example files to demonstrate how it works.

Example of use:

== Input file contents ==
Height: 132 
Name: Steven Rose
DOB: 14/12/1800
Height: 54
Name: Michelle Road
DOB: 14/12/1945

== Configuration file ==
Height:,4
Name:,14
DOB:,12

== Output file contents ==
132	Steven Rose	14/12/1800	
54	Michelle Road	14/12/1945	