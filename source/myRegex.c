#include "myRegex.h"

void test()
{    
    // 要被批配的 buffer 跟一些參數
    int status, len;
    char buf[1024], data[1024];
    getdata(data);

    // 正規表示式的 pattern 會要先 compile (regcomp();)
    // 並儲存在 regex_t 此資料結構
    regex_t reg;

    // 設定批配模式的 flag. 
    // REG_EXTENDED 萬用
    // REG_ICASE    忽略大小寫
    // REG_NOSUB    不儲存批配後的結果
    // REG_NEWLINE  識別換行符(^$ 這類符號會從每行每行批配)
    int cflags = REG_EXTENDED | REG_ICASE;

    // Pattern 批配的樣板
    const char * pattern = "bus width:\t[0-9]+";

    // 
    regmatch_t pmatch[1];
    size_t nmatch = 1;
    int num;

    // compile pattern 
    regcomp(&reg, pattern, cflags);
    status = regexec(&reg, data, nmatch, pmatch, REG_NOTEOL);
    if (status == REG_NOMATCH) 
        printf("No Match\n");
    else if (status == 0) {
        len = pmatch[0].rm_eo - pmatch[0].rm_so;
        strncpy(buf, data + pmatch[0].rm_so, len);
        buf[len] = '\0';
        sscanf(buf, "bus width:\t%d", &num);
        printf("%d\n", num);
    }

    sscanf(data, "bus width: %d", &num);
    printf("%d\n", num);

    regfree(&reg);
    return;
}

void getdata(char* buf)
{
	FILE *pFile = fopen("data/data", "r");
    
    if (NULL == pFile) 
    {
        printf("Open data failure.\n");
        return;
    } 
    
    fread(buf, 1024, 1, pFile);
    fclose(pFile);
}

void getsampletext(char* buf)
{
    strncpy(buf, "clock:\t\t52000000 Hz\
                vdd:\t\t21 (3.3 ~ 3.4 V)\
                bus mode:\t2 (push-pull)\
                chip select:\t0 (don't care)\
                power mode:\t2 (on)\
                bus width:\t3 (8 bits)\
                timing spec:\t1 (mmc high-speed)\
                signal voltage:\t0 (3.30 V)\
                driver type:\t0 (driver type B)", 1024);
    return;
}