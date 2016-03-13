/*
 * encapsulate.c - test encapsulate and decapsulate
 *
 * Copyright (C) 2014 - 2016, Xiaoxiao <i@pxx.io>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "../src/compress.h"
#include "../src/crypto.h"
#include "../src/encapsulate.h"


int main()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((int)((tv.tv_sec * 1000 + tv.tv_usec / 1000) % RAND_MAX));

    if (compress_init() != 0)
    {
        return -1;
    }

    crypto_init("8556085d7ff5655a5e09a385c152ea2a");

    const int mtu = 1452;

    pbuf_t pbuf;
    int n;

    // these code generate test data used bellow
    /*
    for (int i = 0; i < 1024; i++)
    {
        pbuf.payload[i] = (i % 2) ? 0x55u : 0xaau;
    }
    pbuf.len = 1024;
    pbuf.flag = 0x0000;
    pbuf.ack = 0;
    n = encapsulate(&pbuf, mtu);
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("\\x%02x", ((uint8_t *)&pbuf)[i]);
    }
    printf("\n");

    for (int i = 0, c = 0; i < 1024; i++)
    {
        c = (32771 * c + 10007) % 65537;
        pbuf.payload[i] = (c & 0xffu);
    }
    pbuf.len = 1024;
    pbuf.flag = 0x0000;
    pbuf.ack = 0;
    n = encapsulate(&pbuf, mtu);
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("\\x%02x", ((uint8_t *)&pbuf)[i]);
    }
    printf("\n");
    */

    uint8_t test1[] =
        "\x23\x31\x50\x36\x32\x74\xf2\x54\x77\x41\x68\xf2\x55\x0b\x9e\x1a"
        "\x1b\x17\xa0\x4f\x33\x23\x1d\x19\x4f\xea\xdb\xf2\x43\x13\x9f\xe7"
        "\xb3\x96\x0c\x64\xc5\x79\xe1\xf7\xf1\x9b\x6b\x12\xdd\x9e\x9f\x44"
        "\x89\x1d\x01\xb9";
    memcpy(&pbuf, test1, sizeof(test1));
    n = decapsulate(&pbuf, sizeof(test1));
    assert(n == 1024);
    assert(pbuf.len == 1024);
    for (int i = 0; i < n; i++)
    {
        assert(pbuf.payload[i] == ((i % 2) ? 0x55u : 0xaau));
    }

    uint8_t test2[] =
        "\xab\xcb\x7f\x4f\xcd\x33\x1d\xf4\x9b\x18\xf3\xe2\x50\x49\x70\x5c"
        "\x56\x9f\x21\x7c\xf4\x51\x47\x8a\x0d\x13\x4a\x73\xfc\x28\x3d\x83"
        "\xdc\xbf\xee\xcc\x47\x6f\xf1\xa9\xa1\x0e\x0f\x96\xe4\xf2\x9a\x87"
        "\x8d\x80\x00\x1f\xd0\xf4\xba\x14\xcb\x50\x7f\x64\x1d\x7c\xb6\xdf"
        "\x00\xe7\x65\x85\xd1\x88\x52\x11\x5e\xbd\x07\x1c\x6d\x79\xdb\x08"
        "\xe7\x18\x12\xa4\x39\x6e\x1c\xce\xe8\x3c\xc7\xed\x37\x03\x4e\x25"
        "\x87\x2b\x31\xe8\x5b\x81\x95\xb8\x20\x2b\xfa\xc3\x4f\x18\x12\x1f"
        "\x52\xe9\xb8\xe8\x4f\xf2\x80\x29\x54\xb7\xd9\xe4\xe9\x45\x13\xc7"
        "\xf3\xd9\x06\xf0\xd5\x49\xef\x83\x3e\x47\x02\xfb\xf2\x9c\x5a\xd8"
        "\x97\xab\x16\xff\xdf\x48\x43\xa0\x12\xcb\xa6\x78\x19\x77\xeb\x35"
        "\x7f\xed\xdc\x0c\x5f\xb5\x98\x2b\xf6\xb6\x79\x27\x5a\xaa\xc0\x5b"
        "\x8c\x91\xca\x04\x44\x90\x09\x84\x8f\xb5\x0f\xa2\xd5\x77\xa9\x8b"
        "\x58\xdd\x49\xde\xe9\x03\xcf\x06\x0c\xd1\x03\xcc\xda\x2c\xd2\x4f"
        "\x89\xd7\x0d\x64\x72\x70\x9b\xae\x59\x4d\xc5\xf5\x72\xde\xd1\xce"
        "\x10\x24\xcb\xf7\xfd\x3a\x8e\x6b\x70\xb0\x11\x31\xce\x79\xa0\xe0"
        "\xeb\x1e\xba\x3f\x13\xd0\x15\x90\x44\xf9\x94\xfb\x01\x13\xb8\x52"
        "\x49\x1a\xf3\xf4\xb9\x0c\x89\xad\x1a\x04\xc9\x12\xea\x5a\x03\x9e"
        "\xda\x0c\x56\x74\xd3\x29\xc1\x75\xda\x26\x32\x75\xe4\x8c\xe5\xd0"
        "\x9f\x4c\x5b\xb7\x16\xa5\xfa\x4f\x1d\x53\xdb\x87\x39\xb2\x15\xa2"
        "\x5f\x67\x11\x32\x3c\xff\x36\x56\x60\xd6\xa5\xfd\x9d\x6b\x6a\x56"
        "\x66\x21\x13\xc8\xdb\xdb\x30\xde\x8e\x7a\x13\xfe\x03\x63\xee\xe8"
        "\xa9\xd6\xcf\xba\x9a\xf4\x9b\x7e\x6a\xa9\x22\x34\x5b\x8d\x99\xab"
        "\xb3\x15\xec\xd9\x46\xfd\x3b\x8a\xfc\x94\x96\xf0\x08\x04\x40\xfa"
        "\xc4\xad\x2c\x53\xf4\xdb\x61\xe6\xa8\x46\x44\xbd\x90\xd2\x62\x5c"
        "\xce\x64\x55\xa8\x9a\xd5\xbf\x6f\x74\x08\x59\xdd\xb1\x1a\xd4\x10"
        "\x63\x20\xe8\x15\x6a\x19\xca\x30\xe9\x18\x20\x40\x37\x52\x6e\xd0"
        "\xc0\xe2\x04\xa4\x80\xb7\x4f\x83\xbf\xde\x4d\xa8\x81\xad\x19\x61"
        "\x06\xab\xa1\xe5\x59\xf4\x0a\xd6\xf5\xce\x99\x39\x10\x35\x01\x6a"
        "\x15\xcc\xd7\x92\xb4\x32\xac\xa3\x43\xd4\xa2\x49\x7a\x1a\xec\x96"
        "\x00\xe3\x26\x61\xd1\xd0\xe0\x5a\x0a\xe1\xe5\x67\x8e\xb0\xfe\xb8"
        "\xcf\xd1\x7e\x9e\x91\xed\x8f\x44\x02\x27\x00\xb2\xed\x4d\xbd\x5b"
        "\xb7\x6e\x92\x12\xe2\x79\x21\x5b\x32\x7d\x56\xfb\x1b\xb9\x5e\xb7"
        "\xd3\x9b\xfb\x60\xb0\x98\xa0\xb5\x15\xb0\xf5\x9d\x39\x90\xff\xa0"
        "\x93\x5a\x19\x0a\x82\x5b\x83\xc4\x82\xd6\x3b\x87\xfd\x4c\xae\xb2"
        "\x99\x97\x39\x37\x98\x05\x53\x0c\x28\xea\xc2\x67\x4e\x16\x07\x42"
        "\x9b\x8b\xf3\x1b\x68\x86\x1c\x4f\x93\x5b\x17\x2f\xd4\xb7\x51\x45"
        "\xf1\xc5\x5f\x52\xf7\x6f\x5e\xb3\xc3\x72\xc3\x8e\xe5\xfb\x64\xcd"
        "\xb3\x92\xb8\x39\x2a\xb3\x41\x27\x7b\x65\x47\xc2\x0f\x00\x35\x4e"
        "\xc4\x6e\xfb\xec\x43\xe7\x83\x7d\x47\xd8\x40\x44\x11\x6b\xf0\x52"
        "\xf3\xaa\x3d\xf3\x99\x7b\x5d\x6c\x14\xda\x1d\xb4\x46\xf0\x7f\x72"
        "\x03\x28\xcb\xf4\x5e\xc1\xce\x73\x55\x69\xce\xd8\x8d\x8e\x45\x41"
        "\x55\xd7\x2c\x86\xc0\x28\xbd\x87\x76\x9a\x30\x58\x0d\xa7\xd6\xc0"
        "\xd4\x32\xb7\xa3\x36\x06\xef\xf3\xbe\xa0\xec\x54\xbd\x74\xaa\x34"
        "\xfa\x69\xe3\x9b\x76\xd6\x01\x2d\xd9\x11\xc8\x9a\xf1\x22\xec\xc1"
        "\xe7\xa9\x1d\xc8\x4b\xc2\xf5\x10\x1d\x10\x07\xd1\x05\x5b\x3c\x95"
        "\xa8\x22\xc2\x32\xab\xb4\xfa\xc7\xdd\xf7\xe0\x16\x8f\x9b\x73\x73"
        "\x16\x5e\xeb\x19\xe3\xb7\x6d\x1e\x1b\x8e\x34\x0d\x7b\xf5\xa6\xa2"
        "\xa2\xc9\x09\x6c\xac\x46\xa1\xec\x53\x03\x7e\xf7\xef\xa6\xca\x22"
        "\xbe\x4c\xe0\x16\x4d\x2d\xdd\x3b\x40\x22\x40\xcd\x8e\x90\x3b\xd1"
        "\x1b\xbb\x35\xc0\x5a\x8e\x0f\x39\x76\xb3\xe7\xb4\xaf\x78\x98\x9c"
        "\x47\x26\xc0\x96\x6a\x64\xdf\xa6\xcd\xb8\x95\x50\x0a\xce\x1b\x62"
        "\x66\x28\xa9\x19\x1d\x65\x10\xb2\x5b\x81\xbf\xd4\x61\x6e\xbc\x14"
        "\xba\xcd\xdf\xe3\xb2\xa7\xad\x8d\x70\x64\xc1\xdc\x2e\x90\x2b\xcf"
        "\x13\xd6\x8b\x26\x9f\xef\xfb\x19\x8b\xa9\xf9\x07\x57\x06\x2e\xc3"
        "\x90\xed\x7e\xaa\xa5\xf3\x7b\x5d\x0f\x72\x86\xa7\x16\xd2\xf3\x5f"
        "\x32\xa7\x33\x1a\xbe\x17\x75\xc4\x79\x58\x85\x2e\x78\xe8\xc5\xd7"
        "\x7e\x53\x6e\x81\x1a\xa4\x03\xe1\x90\x36\xef\xb6\xa8\x6e\x6e\xd8"
        "\x76\x79\x5a\xef\x0d\xe4\x58\x12\x19\xcf\x98\x8a\x97\x21\xfd\xf0"
        "\xf8\x76\x57\x64\xff\x38\x0b\xfb\x03\xc8\x9a\x20\x2a\x10\x20\xfe"
        "\xa8\x76\xe0\xdc\xb9\x36\x49\xa4\xdc\x82\x6b\x6a\x45\x80\x49\x94"
        "\x75\xb6\xa7\xa0\xa7\x31\x31\x18\x10\xf8\xbb\x51\x7b\x76\xf1\x7e"
        "\x77\xa8\x2f\x5d\xe4\x11\x64\xdf\xb7\x04\x57\xdd\x54\x4c\xce\x6c"
        "\xae\x8b\x30\x3c\xb9\x01\xa4\x1a\xfa\x69\x1d\xb3\x7d\xdf\x29\x0e"
        "\xa6\x00\x40\xba\x98\xfd\x8d\x1c\xfe\x07\xb8\xa1\x4f\x3a\x61\xec"
        "\x6c\xf3\x10\x7a\xc5\x0c\x0f\x75\xfa\xdd\x77\xca\x27\x6a\xd1\x2b"
        "\x86\x1d\xd7\x4c\xa6\xf1\x63\xdb\x6b\xd3\x58\x8d\xfb\xb1\xb0\x5d"
        "\xb0\x3b\x40\xf6\x66\xd2\xde\x27\x6b\x18\x83\x2e\x7d\xc3\xfe\xb2"
        "\x68\x16\xf9\xa3\x8b\xe8\xbc\xd9\x89\xfd\x05\x57\x85\x55\xef\x0e"
        "\xc6\xfa\x58\x35\xe4\x84\x92\x60\x10\xf3\x4f\x6e\x84\x4c\xdf\x3a"
        "\xfc\xf4\xd6\xf2\xc7\xaf\xd7\xcf\xc9\xa8\x5d\x98\xde\xcb\x23\x0f"
        "\x7f\xc1\x01\x96\xff\x31\xdf\xe6\x99\xb7\x5f\x53\xae\xbf\xb3\x67"
        "\x7c\x21\x9a\x0e\x9b\xaf\xf8\xaa\x3d\xa9\xac\x7d\x16\xcd\xe7\x45"
        "\x8d\x87\x68\xcb\xd2\xf7\x28\xc1\x21\x49\xb6\x5d\x68\x3e\x8a\xfd"
        "\x14\x89\x7a\xf0\xea\x0f\xbb\x5d\xaf\xda\x4a\x94\x3e\xcb\x6e\x15"
        "\x29\xf7\x92\x44\x27\x8c\xe6\x1e\x77\xf1\xb0\x15\x56\x85\xa1\x63"
        "\x83\x6a\x4e\x6f\xc6\x27\xa9\x02\xd2\x84\xe1\x2d\x15\x8b";
    memcpy(&pbuf, test2, sizeof(test2));
    n = decapsulate(&pbuf, sizeof(test2));
    assert(n == 1024);
    assert(pbuf.len == 1024);
    for (int i = 0, c = 0; i < n; i++)
    {
        c = (32771 * c + 10007) % 65537;
        assert((pbuf.payload[i]) == (c & 0xffu));
    }

    for (int len = 0; len <= mtu; len++)
    {
        for (int data = 0; data <=2; data++)
        {
            for (int j = 0; j < len; j++)
            {
                if (data == 0)
                {
                    pbuf.payload[j] = (uint8_t)(rand() & 0xffU);
                }
                else if (data == 1)
                {
                    pbuf.payload[j] = (uint8_t)(j & 0xffU);
                }
                else
                {
                    pbuf.payload[j] = (uint8_t)(len & 0xffU);
                }
            }
            pbuf.len = len;
            pbuf.flag = 0x0000;
            pbuf.ack = 0;

            pbuf_t copy;
            copy.ack = pbuf.ack;
            copy.flag = pbuf.flag;
            copy.len = pbuf.len;
            memcpy(copy.payload, pbuf.payload, pbuf.len);

            n = encapsulate(&copy, mtu);
            assert(n <= mtu + PAYLOAD_OFFSET);

            n = decapsulate(&copy, n);
            assert(n >= 0);
            assert(copy.len == pbuf.len);
            assert(memcmp(copy.payload, pbuf.payload, copy.len) == 0);
        }
    }
    return 0;
}
