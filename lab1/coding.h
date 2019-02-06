/* For any character c, encode(c) is a character different from c */
unsigned char encode(unsigned char c);
/* For any character c, decode(encode(c)) == c */
unsigned char decode(unsigned char c);