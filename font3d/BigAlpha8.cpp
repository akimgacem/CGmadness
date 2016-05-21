/*
 * CG Madness - a Marble Madness clone
 * Copyright (C) 2007  Sven Reinck <sreinck@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "BigAlpha8.hpp"

#include "hw/varray.hpp"

float verticesBigAlpha8[224 * 3] = {
7.76771, 1.65573, 1,
7.9875, 1.62292, 1,
7.76771, 1.65573, 0,
7.9875, 1.62292, 0,
8.17604, 1.56823, 1,
8.17604, 1.56823, 0,
8.33333, 1.49167, 1,
8.33333, 1.49167, 0,
8.45729, 1.3849, 1,
8.45729, 1.3849, 0,
8.54583, 1.23958, 1,
8.54583, 1.23958, 0,
8.59896, 1.05573, 1,
8.59896, 1.05573, 0,
8.61667, 0.833333, 1,
8.61667, 0.833333, 0,
8.54792, 0.46875, 1,
8.54792, 0.46875, 0,
8.34167, 0.208333, 1,
8.34167, 0.208333, 0,
7.99792, 0.052083, 1,
7.99792, 0.052083, 0,
7.51667, 0, 1,
7.51667, 0, 0,
2.48333, 0, 1,
2.48333, 0, 0,
2.00208, 0.052083, 1,
2.00208, 0.052083, 0,
1.65833, 0.208333, 1,
1.65833, 0.208333, 0,
1.45208, 0.46875, 1,
1.45208, 0.46875, 0,
1.38333, 0.833333, 1,
1.38333, 0.833333, 0,
1.40104, 1.05573, 1,
1.40104, 1.05573, 0,
1.45417, 1.23958, 1,
1.45417, 1.23958, 0,
1.54271, 1.3849, 1,
1.54271, 1.3849, 0,
1.66667, 1.49167, 1,
1.66667, 1.49167, 0,
1.82396, 1.56823, 1,
1.82396, 1.56823, 0,
2.0125, 1.62292, 1,
2.0125, 1.62292, 0,
2.23229, 1.65573, 1,
2.23229, 1.65573, 0,
2.48333, 1.66667, 1,
2.48333, 1.66667, 0,
4.16667, 1.66667, 1,
4.16667, 1.66667, 0,
4.16667, 8.05, 1,
4.16667, 8.05, 0,
2.48333, 8.05, 1,
2.48333, 8.05, 0,
2.00208, 8.10208, 1,
2.00208, 8.10208, 0,
1.65833, 8.25833, 1,
1.65833, 8.25833, 0,
1.45208, 8.51875, 1,
1.45208, 8.51875, 0,
1.38333, 8.88333, 1,
1.38333, 8.88333, 0,
1.40104, 9.10573, 1,
1.40104, 9.10573, 0,
1.45417, 9.28958, 1,
1.45417, 9.28958, 0,
1.54271, 9.4349, 1,
1.54271, 9.4349, 0,
1.66667, 9.54167, 1,
1.66667, 9.54167, 0,
1.82396, 9.61823, 1,
1.82396, 9.61823, 0,
2.0125, 9.67292, 1,
2.0125, 9.67292, 0,
2.23229, 9.70573, 1,
2.23229, 9.70573, 0,
2.48333, 9.71667, 1,
2.48333, 9.71667, 0,
7.51667, 9.71667, 1,
7.51667, 9.71667, 0,
7.76771, 9.70573, 1,
7.76771, 9.70573, 0,
7.9875, 9.67292, 1,
7.9875, 9.67292, 0,
8.17604, 9.61823, 1,
8.17604, 9.61823, 0,
8.33333, 9.54167, 1,
8.33333, 9.54167, 0,
8.45729, 9.4349, 1,
8.45729, 9.4349, 0,
8.54583, 9.28958, 1,
8.54583, 9.28958, 0,
8.59896, 9.10573, 1,
8.59896, 9.10573, 0,
8.61667, 8.88333, 1,
8.61667, 8.88333, 0,
8.54792, 8.51875, 1,
8.54792, 8.51875, 0,
8.34167, 8.25833, 1,
8.34167, 8.25833, 0,
7.99792, 8.10208, 1,
7.99792, 8.10208, 0,
7.51667, 8.05, 1,
7.51667, 8.05, 0,
5.83333, 8.05, 1,
5.83333, 8.05, 0,
5.83333, 1.66667, 1,
5.83333, 1.66667, 0,
7.51667, 1.66667, 1,
7.51667, 1.66667, 0,
8.54792, 0.46875, 0,
8.45729, 1.3849, 0,
8.34167, 0.208333, 0,
8.54583, 1.23958, 0,
8.59896, 1.05573, 0,
8.61667, 0.833333, 0,
7.76771, 1.65573, 0,
7.99792, 0.052083, 0,
7.9875, 1.62292, 0,
8.17604, 1.56823, 0,
8.33333, 1.49167, 0,
7.51667, 0, 0,
4.16667, 1.66667, 0,
2.48333, 0, 0,
5.83333, 1.66667, 0,
7.51667, 1.66667, 0,
2.23229, 9.70573, 0,
2.48333, 8.05, 0,
2.48333, 9.71667, 0,
7.51667, 9.71667, 0,
4.16667, 8.05, 0,
5.83333, 8.05, 0,
2.0125, 1.62292, 0,
2.00208, 0.052083, 0,
2.23229, 1.65573, 0,
2.48333, 1.66667, 0,
1.45417, 1.23958, 0,
1.65833, 0.208333, 0,
1.54271, 1.3849, 0,
1.66667, 1.49167, 0,
1.82396, 1.56823, 0,
1.45208, 0.46875, 0,
1.40104, 1.05573, 0,
1.38333, 0.833333, 0,
8.54792, 8.51875, 0,
8.45729, 9.4349, 0,
8.34167, 8.25833, 0,
8.54583, 9.28958, 0,
8.59896, 9.10573, 0,
8.61667, 8.88333, 0,
7.76771, 9.70573, 0,
7.99792, 8.10208, 0,
7.9875, 9.67292, 0,
8.17604, 9.61823, 0,
8.33333, 9.54167, 0,
7.51667, 8.05, 0,
1.66667, 9.54167, 0,
2.00208, 8.10208, 0,
1.82396, 9.61823, 0,
2.0125, 9.67292, 0,
1.65833, 8.25833, 0,
1.45417, 9.28958, 0,
1.45208, 8.51875, 0,
1.54271, 9.4349, 0,
1.40104, 9.10573, 0,
1.38333, 8.88333, 0,
8.54792, 0.46875, 1,
8.45729, 1.3849, 1,
8.34167, 0.208333, 1,
8.54583, 1.23958, 1,
8.59896, 1.05573, 1,
8.61667, 0.833333, 1,
7.76771, 1.65573, 1,
7.99792, 0.052083, 1,
7.9875, 1.62292, 1,
8.17604, 1.56823, 1,
8.33333, 1.49167, 1,
7.51667, 0, 1,
4.16667, 1.66667, 1,
2.48333, 0, 1,
5.83333, 1.66667, 1,
7.51667, 1.66667, 1,
2.23229, 9.70573, 1,
2.48333, 8.05, 1,
2.48333, 9.71667, 1,
7.51667, 9.71667, 1,
4.16667, 8.05, 1,
5.83333, 8.05, 1,
2.0125, 1.62292, 1,
2.00208, 0.052083, 1,
2.23229, 1.65573, 1,
2.48333, 1.66667, 1,
1.45417, 1.23958, 1,
1.65833, 0.208333, 1,
1.54271, 1.3849, 1,
1.66667, 1.49167, 1,
1.82396, 1.56823, 1,
1.45208, 0.46875, 1,
1.40104, 1.05573, 1,
1.38333, 0.833333, 1,
8.54792, 8.51875, 1,
8.45729, 9.4349, 1,
8.34167, 8.25833, 1,
8.54583, 9.28958, 1,
8.59896, 9.10573, 1,
8.61667, 8.88333, 1,
7.76771, 9.70573, 1,
7.99792, 8.10208, 1,
7.9875, 9.67292, 1,
8.17604, 9.61823, 1,
8.33333, 9.54167, 1,
7.51667, 8.05, 1,
1.66667, 9.54167, 1,
2.00208, 8.10208, 1,
1.82396, 9.61823, 1,
2.0125, 9.67292, 1,
1.65833, 8.25833, 1,
1.45417, 9.28958, 1,
1.45208, 8.51875, 1,
1.54271, 9.4349, 1,
1.40104, 9.10573, 1,
1.38333, 8.88333, 1,
};

float normalsBigAlpha8[224 * 3] = {
0.147653, 0.989039, 0,
0.278573, 0.960415, 0,
0.147653, 0.989039, 0,
0.278573, 0.960415, 0,
0.437661, 0.89914, 0,
0.437661, 0.89914, 0,
0.652625, 0.757681, 0,
0.652625, 0.757681, 0,
0.853962, 0.520335, 0,
0.853962, 0.520335, 0,
0.960698, 0.277595, 0,
0.960698, 0.277595, 0,
0.996845, 0.079374, 0,
0.996845, 0.079374, 0,
0.982681, -0.185306, 0,
0.982681, -0.185306, 0,
0.783919, -0.620864, 0,
0.783919, -0.620864, 0,
0.413803, -0.910366, 0,
0.413803, -0.910366, 0,
0.107597, -0.994195, 0,
0.107597, -0.994195, 0,
-0, -1, 0,
-0, -1, 0,
-0.107597, -0.994195, 0,
-0.107597, -0.994195, 0,
-0.413803, -0.910366, 0,
-0.413803, -0.910366, 0,
-0.783919, -0.620864, 0,
-0.783919, -0.620864, 0,
-0.982681, -0.185306, 0,
-0.982681, -0.185306, 0,
-0.996845, 0.079374, 0,
-0.996845, 0.079374, 0,
-0.960698, 0.277595, 0,
-0.960698, 0.277595, 0,
-0.853962, 0.520335, 0,
-0.853962, 0.520335, 0,
-0.652625, 0.757681, 0,
-0.652625, 0.757681, 0,
-0.437661, 0.89914, 0,
-0.437661, 0.89914, 0,
-0.278573, 0.960415, 0,
-0.278573, 0.960415, 0,
-0.147653, 0.989039, 0,
-0.147653, 0.989039, 0,
-0.043527, 0.999052, 0,
-0.043527, 0.999052, 0,
-0, 1, 0,
-0, 1, 0,
-1, 0, 0,
-1, 0, 0,
-0, -1, 0,
-0, -1, 0,
-0.107597, -0.994195, 0,
-0.107597, -0.994195, 0,
-0.413803, -0.910366, 0,
-0.413803, -0.910366, 0,
-0.783919, -0.620864, 0,
-0.783919, -0.620864, 0,
-0.982681, -0.185306, 0,
-0.982681, -0.185306, 0,
-0.996845, 0.079374, 0,
-0.996845, 0.079374, 0,
-0.960698, 0.277595, 0,
-0.960698, 0.277595, 0,
-0.853962, 0.520335, 0,
-0.853962, 0.520335, 0,
-0.652625, 0.757681, 0,
-0.652625, 0.757681, 0,
-0.437661, 0.89914, 0,
-0.437661, 0.89914, 0,
-0.278573, 0.960415, 0,
-0.278573, 0.960415, 0,
-0.147653, 0.989039, 0,
-0.147653, 0.989039, 0,
-0.043527, 0.999052, 0,
-0.043527, 0.999052, 0,
-0, 1, 0,
-0, 1, 0,
0.043527, 0.999052, 0,
0.043527, 0.999052, 0,
0.147653, 0.989039, 0,
0.147653, 0.989039, 0,
0.278573, 0.960415, 0,
0.278573, 0.960415, 0,
0.437661, 0.89914, 0,
0.437661, 0.89914, 0,
0.652625, 0.757681, 0,
0.652625, 0.757681, 0,
0.853962, 0.520335, 0,
0.853962, 0.520335, 0,
0.960698, 0.277595, 0,
0.960698, 0.277595, 0,
0.996845, 0.079374, 0,
0.996845, 0.079374, 0,
0.982681, -0.185306, 0,
0.982681, -0.185306, 0,
0.783919, -0.620864, 0,
0.783919, -0.620864, 0,
0.413803, -0.910366, 0,
0.413803, -0.910366, 0,
0.107597, -0.994195, 0,
0.107597, -0.994195, 0,
-0, -1, 0,
-0, -1, 0,
1, 0, 0,
1, 0, 0,
-0, 1, 0,
-0, 1, 0,
0.043527, 0.999052, 0,
0.043527, 0.999052, 0,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, -1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
0, 0, 1,
};

unsigned int indicesBigAlpha8[660] = {
0, 1, 2,
1, 3, 2,
1, 4, 3,
4, 5, 3,
4, 6, 5,
6, 7, 5,
6, 8, 7,
8, 9, 7,
8, 10, 9,
10, 11, 9,
10, 12, 11,
12, 13, 11,
12, 14, 13,
14, 15, 13,
14, 16, 15,
16, 17, 15,
16, 18, 17,
18, 19, 17,
18, 20, 19,
20, 21, 19,
20, 22, 21,
22, 23, 21,
22, 24, 23,
24, 25, 23,
24, 26, 25,
26, 27, 25,
26, 28, 27,
28, 29, 27,
28, 30, 29,
30, 31, 29,
30, 32, 31,
32, 33, 31,
32, 34, 33,
34, 35, 33,
34, 36, 35,
36, 37, 35,
36, 38, 37,
38, 39, 37,
38, 40, 39,
40, 41, 39,
40, 42, 41,
42, 43, 41,
42, 44, 43,
44, 45, 43,
44, 46, 45,
46, 47, 45,
46, 48, 47,
48, 49, 47,
48, 50, 49,
50, 51, 49,
50, 52, 51,
52, 53, 51,
52, 54, 53,
54, 55, 53,
54, 56, 55,
56, 57, 55,
56, 58, 57,
58, 59, 57,
58, 60, 59,
60, 61, 59,
60, 62, 61,
62, 63, 61,
62, 64, 63,
64, 65, 63,
64, 66, 65,
66, 67, 65,
66, 68, 67,
68, 69, 67,
68, 70, 69,
70, 71, 69,
70, 72, 71,
72, 73, 71,
72, 74, 73,
74, 75, 73,
74, 76, 75,
76, 77, 75,
76, 78, 77,
78, 79, 77,
78, 80, 79,
80, 81, 79,
80, 82, 81,
82, 83, 81,
82, 84, 83,
84, 85, 83,
84, 86, 85,
86, 87, 85,
86, 88, 87,
88, 89, 87,
88, 90, 89,
90, 91, 89,
90, 92, 91,
92, 93, 91,
92, 94, 93,
94, 95, 93,
94, 96, 95,
96, 97, 95,
96, 98, 97,
98, 99, 97,
98, 100, 99,
100, 101, 99,
100, 102, 101,
102, 103, 101,
102, 104, 103,
104, 105, 103,
104, 106, 105,
106, 107, 105,
106, 108, 107,
108, 109, 107,
108, 110, 109,
110, 111, 109,
110, 0, 111,
0, 2, 111,
112, 113, 114,
112, 115, 113,
112, 116, 115,
112, 117, 116,
118, 119, 120,
119, 121, 120,
119, 114, 121,
114, 122, 121,
114, 113, 122,
123, 124, 125,
123, 126, 124,
123, 127, 126,
123, 118, 127,
123, 119, 118,
128, 129, 130,
129, 131, 130,
129, 132, 131,
132, 133, 131,
132, 124, 133,
124, 126, 133,
125, 134, 135,
125, 136, 134,
125, 137, 136,
125, 124, 137,
138, 139, 140,
139, 141, 140,
139, 135, 141,
135, 142, 141,
135, 134, 142,
143, 144, 145,
143, 138, 144,
143, 139, 138,
146, 147, 148,
146, 149, 147,
146, 150, 149,
146, 151, 150,
152, 153, 154,
153, 155, 154,
153, 148, 155,
148, 156, 155,
148, 147, 156,
157, 131, 133,
157, 152, 131,
157, 153, 152,
158, 159, 160,
159, 161, 160,
159, 129, 161,
129, 128, 161,
162, 163, 164,
162, 165, 163,
162, 158, 165,
162, 159, 158,
164, 166, 167,
164, 163, 166,
168, 169, 170,
168, 171, 169,
168, 172, 171,
168, 173, 172,
174, 175, 176,
175, 177, 176,
175, 170, 177,
170, 178, 177,
170, 169, 178,
179, 180, 181,
179, 182, 180,
179, 183, 182,
179, 174, 183,
179, 175, 174,
184, 185, 186,
185, 187, 186,
185, 188, 187,
188, 189, 187,
188, 180, 189,
180, 182, 189,
181, 190, 191,
181, 192, 190,
181, 193, 192,
181, 180, 193,
194, 195, 196,
195, 197, 196,
195, 191, 197,
191, 198, 197,
191, 190, 198,
199, 200, 201,
199, 194, 200,
199, 195, 194,
202, 203, 204,
202, 205, 203,
202, 206, 205,
202, 207, 206,
208, 209, 210,
209, 211, 210,
209, 204, 211,
204, 212, 211,
204, 203, 212,
213, 187, 189,
213, 208, 187,
213, 209, 208,
214, 215, 216,
215, 217, 216,
215, 185, 217,
185, 184, 217,
218, 219, 220,
218, 221, 219,
218, 214, 221,
218, 215, 214,
220, 222, 223,
220, 219, 222,
};

void drawBigAlpha8()
{
drawTrianglesVerticesNormalsIndices(660, verticesBigAlpha8, normalsBigAlpha8, indicesBigAlpha8);
}