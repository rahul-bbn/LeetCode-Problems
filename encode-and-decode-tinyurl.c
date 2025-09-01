#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URLS 10000
#define BASE_URL "http://tinyurl.com/"

char* url_db[MAX_URLS];
int counter = 0;

/** Encodes a URL to a shortened URL. */
char* encode(char* longUrl) {
    url_db[counter]=strdup(longUrl);   // save original URL
    char* tiny=(char*)malloc(100);
    sprintf(tiny, "%s%d", BASE_URL, counter); // make short url
    counter++;
    return tiny; // caller must free
}

/** Decodes a shortened URL to its original URL. */
char* decode(char* shortUrl) {
    int id=atoi(strrchr(shortUrl, '/') + 1); // get number after last '/'
    return url_db[id];
}

// Your functions will be called as such:
// char* s = encode(s);
// decode(s);