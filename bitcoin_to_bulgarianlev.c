// Basic code that you can use for price checking Bitcoin to Bulgarian Lev // 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Fetch data from the API
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, char* output_buffer) {
    strcpy(output_buffer, (char*)contents);
    return size * nmemb;
}

double getBtcToBgnExchangeRate() {
    // Actual API URL
    const char* api_url = "https://api.example.com/btc-to-bgn";

    CURL* curl;
    CURLcode res;
    char output_buffer[1024];

    curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Error initializing curl.\n");
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, api_url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_buffer);

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "Error fetching data from the API: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        return -1;
    }

    double exchange_rate;
    sscanf(output_buffer, "%lf", &exchange_rate);

    curl_easy_cleanup(curl);

    return exchange_rate;
}

int main() {
    double btc_amount;
    double bgn_amount;
    double exchange_rate;

    // API call or manual exchange rate
    exchange_rate = getBtcToBgnExchangeRate();

    if (exchange_rate <= 0) {
        printf("Error fetching exchange rate data.\n");
        return 1;
    }

    printf("BTC amount -> ");
    scanf("%lf", &btc_amount);

    bgn_amount = btc_amount * exchange_rate;

    printf("%.2f BTC is equivalent to %.2f BGN\n", btc_amount, bgn_amount);

    return 0;
}