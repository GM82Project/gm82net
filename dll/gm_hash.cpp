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

#include "gm.h"

#include "StringConversion.h"

MD5 gm_md5;
SHA1 gm_sha1;

gmexport double md5_begin() {
	gm_md5.Begin();
	return 1;
}

gmexport double md5_end() {
	gm_md5.End();
	return 1;
}

gmexport double md5_read_file(const char* filename) {
	return (gm_md5.ReadFile(filename))? 1 : 0;
}

gmexport double md5_read_string(const char* string) {
	gm_md5.ReadMem(string, strlen(string));
	return 1;
}

gmexport double md5_read_buffer(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	gm_md5.ReadMem(b->GetData(), b->GetLength());
	return 1;
}

gmexport double md5_read_buffer_part(double id, double pos, double len) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	unsigned int l = b->GetLength();
	unsigned int _pos = gm_cast<unsigned int>(pos);
	unsigned int _len = gm_cast<unsigned int>(len);
	if(_pos > l) _pos = l;
	if(_len > l - _pos) _len = l - _pos;
	gm_md5.ReadMem(b->GetData() + _pos, _len);
	return 1;
}

gmexport const char* md5_result() {
	gmreturnstring = BinToHex(gm_md5.Result(), 16);
	return gmreturnstring.c_str();
}

gmexport double sha1_begin() {
	gm_sha1.Begin();
	return 1;
}

gmexport double sha1_end() {
	gm_sha1.End();
	return 1;
}

gmexport double sha1_read_file(const char* filename) {
	return (gm_sha1.ReadFile(filename))? 1 : 0;
}

gmexport double sha1_read_string(const char* string) {
	gm_sha1.ReadMem(string, strlen(string));
	return 1;
}

gmexport double sha1_read_buffer(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	gm_sha1.ReadMem(b->GetData(), b->GetLength());
	return 1;
}

gmexport double sha1_read_buffer_part(double id, double pos, double len) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	unsigned int l = b->GetLength();
	unsigned int _pos = gm_cast<unsigned int>(pos);
	unsigned int _len = gm_cast<unsigned int>(len);
	if(_pos > l) _pos = l;
	if(_len > l - _pos) _len = l - _pos;
	gm_sha1.ReadMem(b->GetData() + _pos, _len);
	return 1;
}

gmexport const char* sha1_result() {
	gmreturnstring = BinToHex(gm_sha1.Result(), 20);
	return gmreturnstring.c_str();
}
