There are various non-printing escape characters that can perform tasks such as moving the cursor to a specific location, changing the font and background colors, etc. You can use them to move the cursor to calculated positions to achieve the neat column-based formatting like the output of the ls command. The characters you would want to consider are the following:

\033[l;cH: Moves the cursor to line l and column c. \033[nA: Moves the cursor up n lines. \033[bB: Moves the cursor down n lines. \033[nC: Moves the cursor forward n characters. \033[nD: Moves the cursor backward n characters. \033[2J: Clears the screen and moves the cursor to line 0 and column 0 \033[K : Without moving the cursor, clear the line starting from the current cursor position. \033[s : Store the current cursor position \033[u : Move the cursor back to the previously stored location. For example, the following statement moves the cursor to the the top-left corner of the screen and clears the first line, and returns the cursor back to its original location.

printf("\033[s\033[0;0H\033[K\033[u");

https://www.geeksforgeeks.org/merge-sort-for-linked-list/

SORT -t and r together
sort arguments using new_obj and same linker list sorters!

Check with error flags finally
