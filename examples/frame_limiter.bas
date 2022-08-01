' BFBASIC source for frame limiter demo
' https://github.com/mzattera/bfbasic/
FOR i = 15 TO 231
    PRINT CHR$(27);"[H";
    FOR j = 1 TO 16
        PRINT CHR$(27);"[38;5;";i;"mHello frame limiter."
    NEXT j
NEXT i
