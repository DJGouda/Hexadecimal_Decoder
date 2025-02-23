// @Duren Gouda
// B00949586

#include <stdio.h>
#include <stdint.h>

#define Bytes_100 100 // for up to 100 bytes per line, making this a macros because last time my assign1 marks was cut for taking direct values!!

// this fnction is to extract bits from a byte array, reference - https://stackoverflow.com/questions/77057637/extracting-the-last-n-bits-from-an-array-of-bytes-in-c
uint64_t extract_bits(const uint8_t *bytes, int curr, int num_bits) {
    uint64_t value = 0;
    for (int i = 0; i < num_bits; i++) { // loop for bit extraction
        int byte_index = (curr + i) / 8;
        int bit_index = 7 - ((curr + i) % 8);
        value = (value << 1) | ((bytes[byte_index] >> bit_index) & 0x01); // interger extration
    }
    return value;
}

// this function handles the input, output and extration of the packed int from the bytes
void process_line(int line_number) {
    int B;
    if (scanf("%d", &B) != 1) return;

    if (B == 0) return;

    uint8_t bytes[Bytes_100]; 
    for (int i = 0; i < B; i++) {
        if (scanf("%hhx", &bytes[i]) != 1) return; // used "%hhx" unsigned char type , instead of "%x" int type
    }

    int total_bits = B * 8; // total bits 
    int curr = 0;   // current bit position 
    int count = 1;  // counter unpacked integers 

    while (curr + 5 < total_bits) { 

        int L = extract_bits(bytes, curr, 5); // extraction of L 
        curr += 5;

        if (L == 0) break;

        if (curr + L > total_bits) break;  // check for whether there are enough bits left for the L

        uint64_t extracted_value = extract_bits(bytes, curr, L); // extraction of L-bit

        
        if (extracted_value & (1ULL << (L - 1))) { // for sign extenion
            extracted_value |= (-1ULL << L); // 
        }

        // Print the extracted value
        printf("Line %d, integer %d: %lld\n", line_number, count, (long long)extracted_value);

        curr += L;
        count++; // increment integer counter
    }
}

// this is the main function
int main() {
    int N;
    if (scanf("%d", &N) != 1) return 1;

    for (int i = 1; i <= N; i++) {
        process_line(i);
    }

    return 0;
}