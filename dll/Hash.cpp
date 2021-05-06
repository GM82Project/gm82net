/*
 * Copyright 2010-2013 Maarten Baert
 * maarten-baert@hotmail.com
 * http://www.maartenbaert.be/
 * 
 * This file is part of Http Dll 2.
 * 
 * Http Dll 2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Http Dll 2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with Http Dll 2. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Hash.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

inline uint32_t roll_left(uint32_t x, unsigned int n) {
	return (x << n) | (x >> (32 - n));
}
inline uint32_t reverse_endianness_32(uint32_t a) {
	return (a >> 24) | (a << 24) | ((a & 0xff00) << 8) | ((a & 0xff0000) >> 8);
}

inline void md5_ff(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, unsigned int s, uint32_t t) {
	a += ((b & c) | ((~b) & d)) + x + t;
	a = roll_left(a, s) + b;
}
inline void md5_gg(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, unsigned int s, uint32_t t) {
	a += ((b & d) | (c & (~d))) + x + t;
	a = roll_left(a, s) + b;
}
inline void md5_hh(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, unsigned int s, uint32_t t) {
	a += (b ^ c ^ d) + x + t;
	a = roll_left(a, s) + b;
}
inline void md5_ii(uint32_t& a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, unsigned int s, uint32_t t) {
	a += (c ^ (b | (~d))) + x + t;
	a = roll_left(a, s) + b;
}

// initialize a md5 hash
void md5_init(uint32_t result[4]) {
	result[0] = 0x67452301;
	result[1] = 0xefcdab89;
	result[2] = 0x98badcfe;
	result[3] = 0x10325476;
}

// add 16 words to the md5 hash
void md5_hash(uint32_t result[4], uint32_t block[16]) {
	
	uint32_t a = result[0];
	uint32_t b = result[1];
	uint32_t c = result[2];
	uint32_t d = result[3];
	
	md5_ff(a, b, c, d, block[ 0],  7, 0xd76aa478);
	md5_ff(d, a, b, c, block[ 1], 12, 0xe8c7b756);
	md5_ff(c, d, a, b, block[ 2], 17, 0x242070db);
	md5_ff(b, c, d, a, block[ 3], 22, 0xc1bdceee);
	md5_ff(a, b, c, d, block[ 4],  7, 0xf57c0faf);
	md5_ff(d, a, b, c, block[ 5], 12, 0x4787c62a);
	md5_ff(c, d, a, b, block[ 6], 17, 0xa8304613);
	md5_ff(b, c, d, a, block[ 7], 22, 0xfd469501);
	md5_ff(a, b, c, d, block[ 8],  7, 0x698098d8);
	md5_ff(d, a, b, c, block[ 9], 12, 0x8b44f7af);
	md5_ff(c, d, a, b, block[10], 17, 0xffff5bb1);
	md5_ff(b, c, d, a, block[11], 22, 0x895cd7be);
	md5_ff(a, b, c, d, block[12],  7, 0x6b901122);
	md5_ff(d, a, b, c, block[13], 12, 0xfd987193);
	md5_ff(c, d, a, b, block[14], 17, 0xa679438e);
	md5_ff(b, c, d, a, block[15], 22, 0x49b40821);
	
	md5_gg(a, b, c, d, block[ 1],  5, 0xf61e2562);
	md5_gg(d, a, b, c, block[ 6],  9, 0xc040b340);
	md5_gg(c, d, a, b, block[11], 14, 0x265e5a51);
	md5_gg(b, c, d, a, block[ 0], 20, 0xe9b6c7aa);
	md5_gg(a, b, c, d, block[ 5],  5, 0xd62f105d);
	md5_gg(d, a, b, c, block[10],  9, 0x02441453);
	md5_gg(c, d, a, b, block[15], 14, 0xd8a1e681);
	md5_gg(b, c, d, a, block[ 4], 20, 0xe7d3fbc8);
	md5_gg(a, b, c, d, block[ 9],  5, 0x21e1cde6);
	md5_gg(d, a, b, c, block[14],  9, 0xc33707d6);
	md5_gg(c, d, a, b, block[ 3], 14, 0xf4d50d87);
	md5_gg(b, c, d, a, block[ 8], 20, 0x455a14ed);
	md5_gg(a, b, c, d, block[13],  5, 0xa9e3e905);
	md5_gg(d, a, b, c, block[ 2],  9, 0xfcefa3f8);
	md5_gg(c, d, a, b, block[ 7], 14, 0x676f02d9);
	md5_gg(b, c, d, a, block[12], 20, 0x8d2a4c8a);
	
	md5_hh(a, b, c, d, block[ 5],  4, 0xfffa3942);
	md5_hh(d, a, b, c, block[ 8], 11, 0x8771f681);
	md5_hh(c, d, a, b, block[11], 16, 0x6d9d6122);
	md5_hh(b, c, d, a, block[14], 23, 0xfde5380c);
	md5_hh(a, b, c, d, block[ 1],  4, 0xa4beea44);
	md5_hh(d, a, b, c, block[ 4], 11, 0x4bdecfa9);
	md5_hh(c, d, a, b, block[ 7], 16, 0xf6bb4b60);
	md5_hh(b, c, d, a, block[10], 23, 0xbebfbc70);
	md5_hh(a, b, c, d, block[13],  4, 0x289b7ec6);
	md5_hh(d, a, b, c, block[ 0], 11, 0xeaa127fa);
	md5_hh(c, d, a, b, block[ 3], 16, 0xd4ef3085);
	md5_hh(b, c, d, a, block[ 6], 23, 0x04881d05);
	md5_hh(a, b, c, d, block[ 9],  4, 0xd9d4d039);
	md5_hh(d, a, b, c, block[12], 11, 0xe6db99e5);
	md5_hh(c, d, a, b, block[15], 16, 0x1fa27cf8);
	md5_hh(b, c, d, a, block[ 2], 23, 0xc4ac5665);
	
	md5_ii(a, b, c, d, block[ 0],  6, 0xf4292244);
	md5_ii(d, a, b, c, block[ 7], 10, 0x432aff97);
	md5_ii(c, d, a, b, block[14], 15, 0xab9423a7);
	md5_ii(b, c, d, a, block[ 5], 21, 0xfc93a039);
	md5_ii(a, b, c, d, block[12],  6, 0x655b59c3);
	md5_ii(d, a, b, c, block[ 3], 10, 0x8f0ccc92);
	md5_ii(c, d, a, b, block[10], 15, 0xffeff47d);
	md5_ii(b, c, d, a, block[ 1], 21, 0x85845dd1);
	md5_ii(a, b, c, d, block[ 8],  6, 0x6fa87e4f);
	md5_ii(d, a, b, c, block[15], 10, 0xfe2ce6e0);
	md5_ii(c, d, a, b, block[ 6], 15, 0xa3014314);
	md5_ii(b, c, d, a, block[13], 21, 0x4e0811a1);
	md5_ii(a, b, c, d, block[ 4],  6, 0xf7537e82);
	md5_ii(d, a, b, c, block[11], 10, 0xbd3af235);
	md5_ii(c, d, a, b, block[ 2], 15, 0x2ad7d2bb);
	md5_ii(b, c, d, a, block[ 9], 21, 0xeb86d391);
	
	result[0] += a;
	result[1] += b;
	result[2] += c;
	result[3] += d;
	
}

void MD5::Begin() {
	blocks = 0;
	used = 0;
	md5_init(result.w);
}

bool MD5::ReadFile(const char* fname) {
	FILE* f;
	f = fopen(fname, "rb");
	if(f == NULL) return false;
	for( ; ; ) {
		used += fread(block.x + used, 1, 64 - used, f);
		if(used < 64) break;
		md5_hash(result.w, block.w);
		++blocks;
		used = 0;
	}
	fclose(f);
	return true;
}

void MD5::ReadMem(const void* data, unsigned int datalen) {
	if(datalen == 0) return;
	unsigned int j = 0;
	uint8_t* in = (uint8_t*)(data);
	while(datalen - j >= 64 - used) {
		memcpy(block.x + used, in + j, 64 - used);
		j += 64 - used;
		md5_hash(result.w, block.w);
		++blocks;
		used = 0;
	}
	if(datalen - j > 0) {
		memcpy(block.x + used, in + j, datalen - j);
		used += datalen - j;
	}
}

void MD5::End() {
	block.x[used] = 0x80;
	if(64 - used < 8 + 1) {
		memset(block.x + used + 1, 0, 64 - used - 1);
		md5_hash(result.w, block.w);
		memset(block.x, 0, 64 - 8);
	} else {
		memset(block.x + used + 1, 0, 64 - used - 1 - 8);
	}
	block.w[14] = (blocks << 9) | (used << 3);
	block.w[15] = blocks >> (32 - 9);
	md5_hash(result.w, block.w);
	memset(block.x, 0, 64);
}

// initialize a sha1 hash
void sha1_init(uint32_t result[5]) {
	result[0] = 0x67452301;
	result[1] = 0xefcdab89;
	result[2] = 0x98badcfe;
	result[3] = 0x10325476;
	result[4] = 0xc3d2e1f0;
}

// add 16 words to the sha1 hash
void sha1_hash(uint32_t result[5], uint32_t block[16]) {
	
	uint32_t w[80];
	for(unsigned int t = 0; t < 16; ++t) {
		w[t] = reverse_endianness_32(block[t]);
	}
	for(unsigned int t = 16; t < 80; ++t) {
		w[t] = roll_left(w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16], 1);
	}
	
	uint32_t a = result[0];
	uint32_t b = result[1];
	uint32_t c = result[2];
	uint32_t d = result[3];
	uint32_t e = result[4];
	
	for(unsigned int t = 0; t < 20; ++t) {
		uint32_t temp = roll_left(a, 5) + ((b & c) | ((~b) & d)) + e + w[t] + 0x5a827999;
		e = d;
		d = c;
		c = roll_left(b, 30);
		b = a;
		a = temp;
	}
	for(unsigned int t = 20; t < 40; t++) {
		uint32_t temp = roll_left(a, 5) + (b ^ c ^ d) + e + w[t] + 0x6ed9eba1;
		e = d;
		d = c;
		c = roll_left(b, 30);
		b = a;
		a = temp;
	}
	for(unsigned int t = 40; t < 60; t++) {
		uint32_t temp = roll_left(a, 5) + ((b & c) | (b & d) | (c & d)) + e + w[t] + 0x8f1bbcdc;
		e = d;
		d = c;
		c = roll_left(b, 30);
		b = a;
		a = temp;
	}
	for(unsigned int t = 60; t < 80; t++) {
		uint32_t temp = roll_left(a, 5) + (b ^ c ^ d) + e + w[t] + 0xca62c1d6;
		e = d;
		d = c;
		c = roll_left(b, 30);
		b = a;
		a = temp;
	}
	
	result[0] += a;
	result[1] += b;
	result[2] += c;
	result[3] += d;
	result[4] += e;
	
}

void SHA1::Begin() {
	blocks = 0;
	used = 0;
	sha1_init(result.w);
}

bool SHA1::ReadFile(const char* fname) {
	FILE* f;
	f = fopen(fname, "rb");
	if(f == NULL) return false;
	for( ; ; ) {
		used += fread(block.x + used, 1, 64 - used, f);
		if(used < 64) break;
		sha1_hash(result.w, block.w);
		++blocks;
		used = 0;
	}
	fclose(f);
	return true;
}

void SHA1::ReadMem(const void* data, unsigned int datalen) {
	if(datalen == 0) return;
	unsigned int j = 0;
	uint8_t* in = (uint8_t*)(data);
	while(datalen - j >= 64 - used) {
		memcpy(block.x + used, in + j, 64 - used);
		j += 64 - used;
		sha1_hash(result.w, block.w);
		++blocks;
		used = 0;
	}
	if(datalen - j > 0) {
		memcpy(block.x + used, in + j, datalen - j);
		used += datalen - j;
	}
}

void SHA1::End() {
	block.x[used] = 0x80;
	if(64 - used < 8 + 1) {
		memset(block.x + used + 1, 0, 64 - used - 1);
		sha1_hash(result.w, block.w);
		memset(block.x, 0, 64 - 8);
	} else {
		memset(block.x + used + 1, 0, 64 - used - 1 - 8);
	}
	block.w[14] = reverse_endianness_32(blocks >> (32 - 9));
	block.w[15] = reverse_endianness_32((blocks << 9) | (used << 3));
	sha1_hash(result.w, block.w);
	memset(block.x, 0, 64);
	result.w[0] = reverse_endianness_32(result.w[0]);
	result.w[1] = reverse_endianness_32(result.w[1]);
	result.w[2] = reverse_endianness_32(result.w[2]);
	result.w[3] = reverse_endianness_32(result.w[3]);
	result.w[4] = reverse_endianness_32(result.w[4]);
}
