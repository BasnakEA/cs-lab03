
#include <iostream>
#include <vector>
#include <string>
#include<curl/curl.h>
#include<sstream>
#include<cmath>
#include<cstdio>
#include<windows.h>
//#include "histogram.h"
#include "svg.h"
using namespace std;

vector<double> input_numbers(istream& in, const size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        in >> result[i];
    }
    return result;
}

size_t zero_bin_count(const size_t& number_count) {
    size_t k = sqrt(number_count);
    if (k > 25)
    {
        k = 1 + log2(number_count);
        /*cout << "Sterdjis rule" << endl;
        return k;*/
    }
    //cout << "Emper formula" << endl;
    return k;
}

Input
read_input(istream& in, bool prompt) {
    Input data;
    size_t number_count;

    if (prompt)
    {
        cerr << "Enter number count: ";
        in >> number_count;

        cerr << "Enter numbers: ";
        data.numbers = input_numbers(in, number_count);

        cerr << "Enter column count: ";
        in >> data.bin_count;
    }
    else
    {
        in >> number_count;
        data.numbers = input_numbers(in, number_count);
        in >> data.bin_count;
    }

    if (data.bin_count == 0)
    {
        data.bin_count = zero_bin_count(number_count);
    }


    return data;
}

size_t
write_data(void* items, size_t item_size, size_t item_count, void* ctx) {
    const size_t data_size = item_size * item_count;
    const char* new_items = reinterpret_cast<const char*>(items);
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    buffer->write(new_items, data_size);
    return data_size;
}

Input
download(const string& address) {
    stringstream buffer;

    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            cout << curl_easy_strerror(res) << endl;
            exit(1);
        }
        curl_easy_cleanup(curl);
    }
   return read_input(buffer, false);
}

int main(int argc, char* argv[]) {
    Input input;
    char* format;
    int num;

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-format") == 0)
        {
            if (i != argc - 1)
            {
                format = argv[i+1];
            }
            num = i+1;
            break;
        }
    }
    if (((strcmp(format, "text") != 0) && (strcmp(format, "svg") != 0)) || (num == argc))
    {
        cout << "You need to enter to '-format' and then the format type ('text' or 'svg')!";
        exit(1);
    }

    if (argc > 1)
    {
        if (num == 2)
        {
            input = download(argv[3]);
        }
        else
        {
            input = download(argv[1]);
        }
    }
    else
    {
        input = read_input(cin, true);
    }

    // Îáðàáîòêà äàííûõ
    const auto bins = make_histogram(input);

    // Âûâîä äàííûõ
    if (strcmp(format, "text") == 0)
    {
        show_histogram_text(bins);
    }
    else
    {
        show_histogram_svg(bins);
    }

    return 0;
}
