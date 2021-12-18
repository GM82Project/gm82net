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

#include "StringConversion.h"

#include <climits>

std::string UIntToString(unsigned int x) {
	char buffer[20];
	char *ptr = buffer + sizeof(buffer);
	do {
		*(--ptr) = '0' + x % 10;
	} while((x /= 10) != 0);
	return std::string(ptr, buffer + sizeof(buffer) - ptr);
}

unsigned int StringToUInt(const char* str, size_t len) {
	unsigned int value = 0;
	for(size_t i = 0; i < len; ++i) {
		char c = str[i];
		if(c < '0' || c > '9') break;
		if(value > UINT_MAX / 10) return UINT_MAX;
		unsigned int value10 = value*10;
		if(value10 >= UINT_MAX - (unsigned int) (c - '0')) return UINT_MAX;
		value = value10 + (unsigned int) (c - '0');
	}
	return value;
}

std::string BinToHex(const char* str, size_t len) {
	std::string out(len * 2, '\0');
	for(size_t i = 0; i < len; ++i) {
		unsigned char a = (unsigned char) str[i];
		out[2 * i]     = ((a >> 4) > 9)? 'a' + (a >> 4) - 10 : '0' + (a >> 4);
		out[2 * i + 1] = ((a & 15) > 9)? 'a' + (a & 15) - 10 : '0' + (a & 15);
	}
	return out;
}

std::string HexToBin(const char* str, size_t len) {
	std::string out(len / 2, '\0');
	for(size_t i = 0; i < out.length(); ++i) {
		unsigned char a = str[2 * i];
		unsigned char b = str[2 * i + 1];
		out[i] =
			((('0' <= a && a <= '9')? a - '0' :
			  ('a' <= a && a <= 'f')? 10 + a - 'a' :
			  ('A' <= a && a <= 'F')? 10 + a - 'A' : 0) << 4) |
			 (('0' <= b && b <= '9')? b - '0' :
			  ('a' <= b && b <= 'f')? 10 + b - 'a' :
			  ('A' <= b && b <= 'F')? 10 + b - 'A' : 0);
	}
	return out;
}

inline char Base64EncodeChar(unsigned int n) {
	if(n < 26)
		return 'A' + n;
	if(n < 52)
		return 'a' + n - 26;
	if(n < 62)
		return '0' + n - 52;
	if(n < 63)
		return '+';
	return '/';
}

inline unsigned int Base64DecodeChar(char c) {
	if('A' <= c && c <= 'Z')
		return c - 'A';
	if('a' <= c && c <= 'z')
		return c - 'a' + 26;
	if('0' <= c && c <= '9')
		return c - '0' + 52;
	if(c == '+' || c == '-')
		return 62;
	if(c == '/' || c == '_')
		return 63;
	if(c == '=')
		return 64; // special value: padding character
	return 65; // special value: other character
}

std::string Base64Encode(const char* str, size_t len) {
	std::string out;
	size_t i;
	for(i = 0; i + 3 <= len; i += 3) {
		unsigned int num = ((unsigned char) str[i] << 16) | ((unsigned char) str[i + 1] << 8) | (unsigned char) str[i + 2];
		char outchars[4] = {
			Base64EncodeChar((num >> 18) & 63), Base64EncodeChar((num >> 12) & 63),
			Base64EncodeChar((num >> 6) & 63), Base64EncodeChar(num & 63),
		};
		if(i % 48 == 0 && i != 0)
			out.append("\r\n", 2);
		out.append(outchars, 4);
	}
	if(i < len) {
		if(len - i == 1) {
			unsigned int num = (unsigned char) str[i] << 16;
			char outchars[4] = {
				Base64EncodeChar((num >> 18) & 63), Base64EncodeChar((num >> 12) & 63),
				'=', '=',
			};
			if(i % 48 == 0 && i != 0)
				out.append("\r\n", 2);
			out.append(outchars, 4);
		} else {
			unsigned int num = ((unsigned char) str[i] << 16) | ((unsigned char) str[i + 1] << 8);
			char outchars[4] = {
				Base64EncodeChar((num >> 18) & 63), Base64EncodeChar((num >> 12) & 63),
				Base64EncodeChar((num >> 6) & 63), '=',
			};
			if(i % 48 == 0 && i != 0)
				out.append("\r\n", 2);
			out.append(outchars, 4);
		}
	}
	return out;
}

std::string Base64Decode(const char* str, size_t len) {
	std::string out;
	unsigned int num = 0;
	int chars_read = 0, padding_read = 0;
	for(size_t i = 0; i < len; ++i) {
		unsigned int n = Base64DecodeChar(str[i]);
		if(n < 64) {
			num = (num << 6) | n;
			++chars_read;
		} else if(n == 64) { // padding character
			num = num << 6;
			++chars_read;
			++padding_read;
		} else { // skip other characters
			continue;
		}
		if(chars_read == 4) {
			char outchars[3] = {(char) (num >> 16), (char) (num >> 8), (char) num};
			if(padding_read == 0)
				out.append(outchars, 3);
			else if(padding_read == 1)
				out.append(outchars, 2);
			else if(padding_read == 2)
				out.append(outchars, 1);
			num = 0;
			chars_read = 0;
			padding_read = 0;
		}
	}
	if(chars_read != 0) {
		// simulate extra padding
		while(chars_read != 4) {
			num = num << 6;
			++chars_read;
			++padding_read;
		}
		char outchars[3] = {(char) (num >> 16), (char) (num >> 8), (char) num};
		if(padding_read == 0)
			out.append(outchars, 3);
		else if(padding_read == 1)
			out.append(outchars, 2);
		else if(padding_read == 2)
			out.append(outchars, 1);
	}
	return out;
}
