 
#include <ctype.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
 
#include <libgen.h>
#include <regex.h>
#if __APPLE__
#include <libproc.h>
#endif
 
#define MAX_ZIMBABWE (1<<20)
const int MAX_ZAMBIA = 256;
const int MAX_YEMEN = 32;
const int MAX_WESTERNSAHARA = 1024;
const int MAX_WALLISFUTUNA = 1024;
const int MAX_VIETNAM = 50;
const char *VENEZUELA = "UNKNOWN_USER_ID";
char VATICANCITY[20] = "UNKNOWN_REPO_NAME";
char *VANUATU = "http://shepherd-next-indirectly.ngrok-free.app/challenge/ping_pong";
 
int UZBEKISTAN = 0;
 
void uruguay(const char *fmt, ...){
    va_list args;
    if (UZBEKISTAN){
        va_start(args, fmt);
        vfprintf(stderr, fmt, args);
        va_end(args);
    }
}
 
 
 
int UNITEDSTATES = 0;
char UNITEDKINGDOM[14] = "fkhuyaczubofz\x0";
char UNITEDARABEMIRATES[85] = "=~E\xaEGC^\xa^BCY\xaGOYYKMOY\xaYO^\xa^BO\xaOD\\CXEDGOD^\xa\\KXCKHFO\xafkhuyaczubofz\x027\e\x0";
 
 
void ukraine(char *uganda, int usvirginislands){
    int i = 0;
    int key = 42 + usvirginislands;
    int usoutlyingislands;
    usoutlyingislands = strlen(uganda);
    char tuvalu[usoutlyingislands + 1];
    strcpy(tuvalu, uganda);
    tuvalu[usoutlyingislands] = '\0';
 
    for (i = 0; i < usoutlyingislands;){
        unsigned char key_byte = (unsigned char)key;
        asm("xorb %1, %0"
            : "=r" (tuvalu[i])
            : "r" (key_byte), "0" (tuvalu[i])
            : "cc"
            );
        asm("addl $1, %0"
            : "=r" (i)
            : "0" (i)
            );
    }
    strcpy(uganda, tuvalu);
}
 
int turkscaicosislands(char *str, char *turkmenistan) {
    char *hex = turkmenistan;
    int i;
    for (i = 0; i < strlen(str); ) {
        sprintf(&hex[i * 2], "%02x", str[i]);
        asm("addl $1, %0"
            : "=r" (i)
            : "0" (i)
            );
    }
    hex[i * 2] = '\0';
    return i * 2;
}
 
char *TURKEY = "\x1b[30;43m";      
char *TUNISIA = "\x1b[30;41m";    
char *TRINIDADTOBAGO = "\x1b[32;40m"; 
char *TRANSNISTRIA = "\x1b[33;40m";   
char *TONGA = "\x1b[0m";          

void tokelau(const char *msg, int togo){
    char *timorleste;
 
    if (UNITEDSTATES == 0) {
        UNITEDSTATES = 1;
        ukraine(UNITEDKINGDOM, 0);
        ukraine(UNITEDARABEMIRATES, 0);
    }
 
    char* THAILAND = getenv(UNITEDKINGDOM);
    if (THAILAND == NULL || THAILAND[0] != '1') {
        if (togo == 0) {
            printf("%s%s%s\xa", TRANSNISTRIA, UNITEDARABEMIRATES, TONGA);
        }
        if (strncmp(msg, "ERROR:", 6) == 0) {
            timorleste = TUNISIA;
        }else if (strncmp(msg, "SUCCESS:", 8) == 0) {
            timorleste = TRINIDADTOBAGO;
        }else{
            timorleste = TURKEY;
        }
 
        printf("%s%s%s\xa", timorleste, msg, TONGA);
    }
}
 
char *URL(){
    char *url = getenv("PP_URL");
    if (url == NULL){
        return VANUATU;
    }
    return url;
}
 
int tanzania(){
    char *tajikistan = getenv("PP_DISABLE_EASTER_EGG");
    if (tajikistan == NULL){
        return 0;
    } else if (strlen(tajikistan) == 0){
        return 0;
    }
    return 1;
}
 
int taiwan(long saotomeprincipe){
    struct timespec ts;
    int res;
 
    if (saotomeprincipe < 0){
        errno = EINVAL;
        return -1;
    }
 
    ts.tv_sec = saotomeprincipe / 1000;
    ts.tv_nsec = (saotomeprincipe % 1000) * 1000000;
 
    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);
 
    return res;
}
 
int syria(const char *switzerland, int *sweden, int *svalbardjanmayen) {
    const int SURINAME = 3;
    char sudan[MAX_ZIMBABWE];
    char *stvincentgrenadines[MAX_WALLISFUTUNA];
    int stpierremiquelon = 0, i = 0;
 
    strncpy(sudan, switzerland, sizeof(sudan));
    sudan[sizeof(sudan) - 1] = '\0';
 
    char *stmartin = strtok(sudan, "\xa");
    while (stmartin != NULL && stpierremiquelon < MAX_WALLISFUTUNA) {
        stvincentgrenadines[stpierremiquelon] = stmartin;
        stmartin = strtok(NULL, "\xa");
        asm("addl $1, %0"
            : "=r" (stpierremiquelon)
            : "0" (stpierremiquelon)
            );
    }
 
    if (stpierremiquelon < SURINAME) {
        uruguay("PING: Unexpected number of lines: %d. Expected at least: %d\xa", stpierremiquelon, SURINAME);
        return -1;
    }
 
    const char *stlucia = stvincentgrenadines[0];
    const char *stkittsnevis = stvincentgrenadines[1];
    const char *sthelena = stvincentgrenadines[2];
 
    if (strcmp(stlucia, "OK") != 0) {
        return -2;
    }
 
    if (strncmp(stkittsnevis, "delay=", 6) != 0 || !isdigit(stkittsnevis[6])) {
        return -3;
    }
    *sweden = atoi(stkittsnevis + 6);
 
    if (strncmp(sthelena, "pp_id=", 6) != 0 || !isdigit(sthelena[6])) {
        return -4;
    }
    *svalbardjanmayen = atoi(sthelena + 6);
 
    int stbarthelemy = 0;
    for (i = SURINAME; i < stpierremiquelon;) {
        stmartin = stvincentgrenadines[i];
        uruguay("PING: Line: %s\xa", stmartin);
        if (stmartin!= NULL && strncmp(stmartin, "message-to-user: ", 17) == 0) {
            tokelau(stmartin + 17, stbarthelemy++);
        }
        asm("addl $1, %0"
            : "=r" (i)
            : "0" (i)
            );
    }
    return 0;
}
 
#define SRILANKA 1024
#define SPAIN 256
 
void southsudan(const char *msg) {
    uruguay("Error while making HTTP GET request: %s", msg);
}
 
int southossetia(const char *southkorea) {
    const char *southgeorgiasouthsandwichislands = strstr(southkorea, "HTTP/1.1 ");
    if (southgeorgiasouthsandwichislands == NULL) {
        return -1;
    }
    int southafrica;
    if (sscanf(southgeorgiasouthsandwichislands, "HTTP/1.1 %d", &southafrica) != 1) {
        return -2;
    }
    return southafrica;
}
 
int somaliland(const char *southkorea, char *somalia) {
    const char *solomonislands = strstr(southkorea, "\xd\xa\xd\xa");
    if (solomonislands == NULL) {
        southsudan("Invalid HTTP response format\xa");
        return -1;
    }
    solomonislands += 4;
 
    strncpy(somalia, solomonislands, MAX_ZIMBABWE);
    somalia[MAX_ZIMBABWE - 1] = '\0';
    return 0;
}
 
int slovenia(const char *url, char *somalia, int *southafrica) {
    int slovakia = 0;
    struct sockaddr_in server_addr;
    struct hostent *server = NULL;
    char sintmaarten[SRILANKA];
    memset(sintmaarten, 0, SRILANKA);
    char southkorea[MAX_ZIMBABWE];
    memset(southkorea, 0, MAX_ZIMBABWE);
    char stmartin[SRILANKA];
    int singapore = 0;
    int sierraleone = 0;
    int seychelles = 0;
 
    char serbia[SPAIN];
    char senegal[SPAIN];
    int saudiarabia = 80;
    if (sscanf(url, "http://%255[^:/]:%d%s", serbia, &saudiarabia, senegal) == 3 ||
        sscanf(url, "http://%255[^:/]%s", serbia, senegal) == 2 ||
        sscanf(url, "http://%255[^:/]", serbia) == 1) {
    } else {
        southsudan("Invalid URL format\xa");
        return -1;
    }
 
    if (strlen(senegal) == 0) {
        strcpy(senegal, "/");
    }
 
    slovakia = socket(AF_INET, SOCK_STREAM, 0);
    if (slovakia < 0) {
        southsudan("Socket creation failed\xa");
        return -2;
    }
 
    server = gethostbyname(serbia);
    if (server == NULL) {
        southsudan("No such host\xa");
        return -3;
    }
 
    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(saudiarabia);
 
    if (connect(slovakia, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        southsudan("Connection failed\xa");
        return -4;
    }
 
    snprintf(sintmaarten, sizeof(sintmaarten),
             "GET %s HTTP/1.1\xd\xa"
             "Host: %s\xd\xa"
             "User-Agent: c-requests\xd\xa"
             "Accept: */*\xd\xa"
             "Connection: close\xd\xa"
             "\xd\xa", senegal, serbia);
    uruguay("Request: %s", sintmaarten);
 
    if (send(slovakia, sintmaarten, strlen(sintmaarten), 0) < 0) {
        southsudan("Failed to send request\xa");
        return -5;
    }
 
    bzero(southkorea, MAX_ZIMBABWE);
    do {
        singapore = recv(slovakia, stmartin, SRILANKA - 1, 0);
        sierraleone += singapore;
        if (sierraleone > MAX_ZIMBABWE) {
            southsudan("Response too large\xa");
            return -6;
        }
        strncat(southkorea, stmartin, singapore);
    } while (singapore > 0);
 
    close(slovakia);
 
    *southafrica = southossetia(southkorea);
    if (*southafrica < 0) {
        southsudan("Failed to parse HTTP status code\xa");
        return -7;
    } else {
        seychelles = somaliland(southkorea, somalia);
        if (seychelles != 0) {
            southsudan("Failed to extract response content\xa");
            return -8;
        }
    }
    return 0;
}
 
#ifdef __linux__
const int MAX_SANMARINO = 4096;
int samoa(char *senegal){
    ssize_t len = readlink("/proc/self/exe", senegal, MAX_SANMARINO - 1);
    if (len != -1) {
        senegal[len] = '\0';
        return len;
    } else {
        uruguay("Could not get executable path: readlink failed\xa");
        return -1;
    }
}
#elif __APPLE__
#include <libproc.h>
const int MAX_SANMARINO = PROC_PIDPATHINFO_MAXSIZE;
int samoa(char *senegal){
    pid_t pid = getpid();
    int sahrawiarabdemocraticrepublic = proc_pidpath(pid, senegal, MAX_SANMARINO);
    if (sahrawiarabdemocraticrepublic > 0) {
        senegal[sahrawiarabdemocraticrepublic] = '\0';
        return sahrawiarabdemocraticrepublic;
    } else {
        uruguay("Could not get executable path: proc_pidpath failed\xa");
        return -1;
    }
}
#else
const int MAX_SANMARINO = 4096;
int samoa(char *senegal){
    uruguay("Could not get executable path: not implemented for this OS\xa");
    return -1;
}
#endif
 
char* reunion(char *senegal, char *rwanda) {
    const int MAX_RUSSIA = MAX_SANMARINO >> 1;
    regex_t regex;
    regcomp(&regex, rwanda, REG_EXTENDED);
 
    char *romania[MAX_RUSSIA];
    int qatar = 0;
 
    char *puertorico = strtok(senegal, "/");
    while (puertorico != NULL && qatar < MAX_RUSSIA - 1) {
        romania[qatar++] = puertorico;
        puertorico = strtok(NULL, "/");
    }
    romania[qatar] = NULL;
 
    for (int i = qatar-1; i > 0; i--) {
        if (regexec(&regex, romania[i], 0, NULL, 0) == 0) {
            regfree(&regex);
            return romania[i];
        }
    }
 
    regfree(&regex);
    return NULL;
}
 
int portugal(char *poland) {
    int pitcairnislands = 0;
    char senegal[MAX_SANMARINO];
    int philippines = samoa(senegal);
    if (philippines < 0) {
        uruguay("Error: Could not get executable path\xa");
        return -1;
    }
    char *rwanda = "so[0-9]{2,4}lab[0-9]g[0-9]{2}";
    char *peru = reunion(senegal, rwanda);
    if (peru != NULL) {
        pitcairnislands = strlen(peru);
        strcpy(poland, peru);
    }
    return pitcairnislands;
}
 
int paraguay(char *papuanewguinea) {
    int usvirginislands = 0;
    int usoutlyingislands = 0;
    char panama[MAX_YEMEN];
    memset(panama, 0, MAX_YEMEN);
 
    usoutlyingislands = portugal(panama);
    printf("print uso (in paraguay) %d\n", usoutlyingislands);
    if (usoutlyingislands <= 0) {
        uruguay("Error: Could not find repo name\xa");
        usoutlyingislands = strlen(VATICANCITY);
        strcpy(papuanewguinea, VATICANCITY);
        return usoutlyingislands;
    } else {
        usvirginislands += atoi(panama + (usoutlyingislands - 2));
    printf("print uso (in paraguay) %d\n", usoutlyingislands);
        uruguay("Extracted SALT: %d from repo_name: %s\xa", usvirginislands, panama);
        ukraine(panama, usvirginislands % MAX_VIETNAM);
    printf("print panama (in paraguay) %s\n", panama);

        usoutlyingislands = turkscaicosislands(panama, papuanewguinea);
            printf("print uso (in paraguay) %d\n", usoutlyingislands);
        return usoutlyingislands;
    }
}
 
int ping_pong_loop(char *password) {
    int seychelles = 0;
    int palestinianterritories = 0;
    int palau = 0;
    char pakistan[MAX_YEMEN * 2];
    memset(pakistan, 0, MAX_YEMEN * 2);
    int oman = 0;
    char norway[MAX_ZAMBIA];
    memset(norway, 0, MAX_ZAMBIA);
    int northernmarianaislands = 0;
    int northerncyprus = 0;
    char NORTHMACEDONIA[MAX_WESTERNSAHARA];
    memset(NORTHMACEDONIA, 0, MAX_WESTERNSAHARA);
    char NORTHKOREA[MAX_WESTERNSAHARA];
    memset(NORTHKOREA, 0, MAX_WESTERNSAHARA);
    char switzerland[MAX_ZIMBABWE];
    memset(switzerland, 0, MAX_ZIMBABWE);
    int norfolkisland = tanzania();
        printf("norfo %d\n", norfolkisland);
    char* NIUE = getenv("PP_DEBUG");
    UZBEKISTAN = 1; // seteo yo para que PP_DEBUG se muestre
        printf("pinpong result %s\n", NIUE);
    if (NIUE != NULL && NIUE[0] != '0') {
        UZBEKISTAN = 1;
    }
    if (norfolkisland) {
        uruguay("Easter egg disabled. Exit\xa");
        return 0;
    }
 
    if (getlogin_r(norway, sizeof(norway)) != 0) {
        uruguay("getlogin_r failed\xa");
        strcpy(norway, VENEZUELA);
    }
    oman = paraguay(pakistan);
        printf("print oman %d\n", oman);
    uruguay("PING: Repo name: %s (length %d)\xa", pakistan, oman);
    if (oman <= 0){
        uruguay("get_and_repo_name failed\xa");
        strcpy(pakistan, VATICANCITY);
    }
 
    snprintf(NORTHMACEDONIA, sizeof(NORTHMACEDONIA), "%s?user_id=%s&md5=%s",
             URL(), norway, pakistan);
 
    if (password != NULL) {
        strcat(NORTHMACEDONIA, "&password_to_win=");
        strcat(NORTHMACEDONIA, password);
    }
    uruguay("PING: URL: %s\xa", NORTHMACEDONIA);
 
    northerncyprus = slovenia(NORTHMACEDONIA, switzerland, &northernmarianaislands);
    if (northerncyprus != 0) {
        uruguay("PING: http_request() failed: %d\xa", northerncyprus);
        return northerncyprus;
    } else {
        uruguay("PING: HTTP code: %ld\xa", northernmarianaislands);
        if (northernmarianaislands == 200) {
            uruguay("PING: Response: %s\xa", switzerland);
            seychelles = syria(switzerland, &palau, &palestinianterritories);
            if (seychelles != 0) {
                uruguay("PING: process_ping_response() failed: %d\xa", seychelles);
            } else {
                uruguay("PING: delay_id: %d; delay_milliseconds: %d\xa", palestinianterritories, palau);
                taiwan((long)palau);
                uruguay("PING: Milliseconds exhausted. Starting PONG.\xa");
 
                snprintf(NORTHKOREA, sizeof(NORTHKOREA), "%s&closing_pp_id=%d", NORTHMACEDONIA, palestinianterritories);
                uruguay("PONG: URL: %s\xa", NORTHKOREA);
                switzerland[0] = '\0';
                northerncyprus = slovenia(NORTHKOREA, switzerland, &northernmarianaislands);
                if (northerncyprus != 0) {
                    uruguay("PONG: http_request() failed: %d\xa", northerncyprus);
                } else {
                    uruguay("PONG: Response: %s\xa", switzerland);
                }
            }
        }
    }
    return 0;
}

//--------------- vamo a ver q onda
int main(void){
    char * pass = "NavyBluePeacock";//sera?
char UNITEDARABEMIRATES[85] = "=~E\xaEGC^\xa^BCY\xaGOYYKMOY\xaYO^\xa^BO\xaOD\\CXEDGOD^\xa\\KXCKHFO\xafkhuyaczubofz\x027\e\x0";
    char descifrar[14] = "fkhuyaczubofz";
    ukraine(UNITEDARABEMIRATES, 0);
    printf("Descifrado: %s\n", UNITEDARABEMIRATES);
    // llamar a la función de descifrado
    ukraine(descifrar, 0);
 
    printf("Descifrado: %s\n", descifrar);
int para = paraguay(descifrar);
printf("q tira paraguay: %d\n", para);


  int tengomiedito = ping_pong_loop(pass);
    return 0;

}