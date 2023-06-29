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

gmexport double buffer_create() {
	Buffer *b = NULL; // GCC is complaining for some reason ...
	b = new Buffer();
	try {
		gmdata.buffers.insert(std::pair<unsigned int, Buffer*>(++gmdata.idcounter_buffers, b));
	}
	catch(...) {
		delete b;
		throw;
	}
	return gmdata.idcounter_buffers;
}

gmexport double buffer_destroy(double id) {
	std::map<unsigned int, Buffer*>::iterator it = gmdata.buffers.find(gm_cast<unsigned int>(id));
	if(it == gmdata.buffers.end()) {
		return 0;
	}
	delete it->second;
	gmdata.buffers.erase(it);
	return 1;
}

gmexport double buffer_exists(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	return (b == NULL)? 0 : 1;
}

gmexport const char* buffer_to_string(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return b->ToString();
}

gmexport double buffer_get_pos(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return b->GetPos();
}

gmexport double buffer_get_length(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return b->GetLength();
}

gmexport double buffer_at_end(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return (b->IsAtEnd())? 1 : 0;
}

gmexport double buffer_get_error(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return (b->GetError())? 1 : 0;
}

gmexport double buffer_clear_error(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	b->ClearError();
	return 1;
}

gmexport double buffer_clear(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	b->Clear();
	return 1;
}

gmexport double buffer_set_pos(double id, double pos) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	b->SetPos(gm_cast<unsigned int>(pos));
	return 1;
}

gmexport double buffer_set_size(double id, double len) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	b->SetLength(gm_cast<unsigned int>(len));
	return 1;
}

gmexport double buffer_read_from_file(double id, const char* filename) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return (b->ReadFromFile(filename))? 1 : 0;
}

gmexport double buffer_read_from_file_part(double id, const char* filename, double pos, double len) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return (b->ReadFromFilePart(filename, gm_cast<unsigned int>(pos), gm_cast<unsigned int>(len)))? 1 : 0;
}

gmexport double buffer_write_to_file(double id, const char* filename) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return (b->WriteToFile(filename,false))? 1 : 0;
}
gmexport double buffer_write_to_temp_file(double id, const char* filename) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return (b->WriteToFile(filename,true))? 1 : 0;
}

gmexport double buffer_append_to_file(double id, const char* filename) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return (b->AppendToFile(filename))? 1 : 0;
}

gmexport double buffer_rc4_crypt(double id, const char* key) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	b->RC4Crypt(key, strlen(key));
	return 1;
}

gmexport double buffer_rc4_crypt_buffer(double id, double id2) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	Buffer *b2 = gmdata.FindBuffer(gm_cast<unsigned int>(id2));
	if(b2 == NULL) return 0;
	b->RC4Crypt(b2->GetData(), b2->GetLength());
	return 1;
}

gmexport double buffer_zlib_compress(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	b->ZLibCompress();
	return 1;
}

gmexport double buffer_zlib_uncompress(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return (b->ZLibUncompress())? 1 : 0;
}

gmexport double buffer_read_int8(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return b->ReadType<int8_t>();
}

gmexport double buffer_read_uint8(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return b->ReadType<uint8_t>();
}

gmexport double buffer_read_int16(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return b->ReadType<int16_t>();
}

gmexport double buffer_read_uint16(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return b->ReadType<uint16_t>();
}

gmexport double buffer_read_int32(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return b->ReadType<int32_t>();
}

gmexport double buffer_read_uint32(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return b->ReadType<uint32_t>();
}

gmexport double buffer_read_int64(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return (double)(b->ReadType<int64_t>());
}

gmexport double buffer_read_uint64(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return (double)(b->ReadType<uint64_t>());
}

gmexport double buffer_read_intv(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return b->ReadIntV();
}

gmexport double buffer_read_uintv(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	return b->ReadUIntV();
}

gmexport double buffer_read_float32(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
    float data=b->ReadType<float>();
    if (isnan(data) || isinf(data)) return 0;
	return data;
}

gmexport double buffer_read_float64(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
    double data=b->ReadType<double>();
    if (isnan(data) || isinf(data)) return 0;
    return data;
}

template<typename T, size_t N>
static double buffer_write_num_types(double id, const double (&vals)[N]) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if (b == NULL) return 0.0;

	for (size_t i = 0; i < N; ++i)
		b->WriteType<T>(gm_cast<T>(vals[i]));

	return 1.0;
}

template<typename T>
static double buffer_write_type(double id, double value) {
	return buffer_write_num_types<T>(id, {value});
}

gmexport double buffer_write_int8(double id, double value) {
	return buffer_write_type<int8_t>(id, value);
}

gmexport double buffer_write_uint8(double id, double value) {
	return buffer_write_type<uint8_t>(id, value);
}

gmexport double buffer_write_int16(double id, double value) {
	return buffer_write_type<int16_t>(id, value);
}

gmexport double buffer_write_uint16(double id, double value) {
	return buffer_write_type<uint16_t>(id, value);
}

gmexport double buffer_write_int32(double id, double value) {
	return buffer_write_type<int32_t>(id, value);
}

gmexport double buffer_write_uint32(double id, double value) {
	return buffer_write_type<uint32_t>(id, value);
}

gmexport double buffer_write_int64(double id, double value) {
	return buffer_write_type<int64_t>(id, value);
}

gmexport double buffer_write_uint64(double id, double value) {
	return buffer_write_type<uint64_t>(id, value);
}

gmexport double buffer_write_intv(double id, double value) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	b->WriteIntV(gm_cast<int32_t>(value));
	return 1;
}

gmexport double buffer_write_uintv(double id, double value) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	b->WriteUIntV(gm_cast<uint32_t>(value));
	return 1;
}

gmexport double buffer_write_float32(double id, double value) {
	return buffer_write_type<float>(id, value);
}
gmexport double buffer_write_float32x2(double id, double val1, double val2) {
	return buffer_write_num_types<float>(id, {val1, val2});
}
gmexport double buffer_write_float32x3(double id, double val1, double val2, double val3) {
	return buffer_write_num_types<float>(id, {val1, val2, val3});
}

gmexport double buffer_write_float32x4(double id, double val1, double val2, double val3, double val4) {
	return buffer_write_num_types<float>(id, {val1, val2, val3, val4});
}
gmexport double buffer_write_float32x12(double id, double val1, double val2, double val3, double val4, double val5, double val6, double val7, double val8, double val9, double val10, double val11, double val12) {
	return buffer_write_num_types<float>(id, {val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12});
}

gmexport double buffer_write_float64(double id, double value) {
	return buffer_write_type<double>(id, value);
}

gmexport const char* buffer_read_string(double id) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return "";
	gmreturnstring = b->ReadString();
	return gmreturnstring.c_str();
}

gmexport double buffer_write_string(double id, const char* string) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	b->WriteString(string);
	return 1;
}

gmexport const char* buffer_read_data(double id, double len) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return "";
	unsigned int l = gm_cast<unsigned int>(len);
	gmreturnstring = b->ReadData(l);
	return gmreturnstring.c_str();
}

gmexport double buffer_write_data(double id, const char* string) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	b->WriteData(string, strlen(string));
	return 1;
}

gmexport const char* buffer_read_hex(double id, double len) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return "";
	unsigned int l = gm_cast<unsigned int>(len);
	gmreturnstring = b->ReadHex(l);
	return gmreturnstring.c_str();
}

gmexport double buffer_write_hex(double id, const char* string) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	b->WriteHex(string, strlen(string));
	return 1;
}

gmexport const char* buffer_read_base64(double id, double len) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return "";
	unsigned int l = gm_cast<unsigned int>(len);
	gmreturnstring = b->ReadBase64(l);
	return gmreturnstring.c_str();
}

gmexport double buffer_write_base64(double id, const char* string) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	b->WriteBase64(string, strlen(string));
	return 1;
}

gmexport double buffer_write_buffer(double id, double id2) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	Buffer *b2 = gmdata.FindBuffer(gm_cast<unsigned int>(id2));
	if(b2 == NULL) return 0;
	b->WriteBuffer(b2);
    b->SetPos(b->GetLength() + b2->GetLength());
	return 1;
}

gmexport double buffer_write_buffer_part(double id, double id2, double pos, double len) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
	Buffer *b2 = gmdata.FindBuffer(gm_cast<unsigned int>(id2));
	if(b2 == NULL) return 0;
	b->WriteBufferPart(b2, gm_cast<unsigned int>(pos), gm_cast<unsigned int>(len));
    b->SetPos(b->GetLength() + gm_cast<unsigned int>(len));
	return 1;
}

gmexport double buffer_get_address(double id, double asrealpointer) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if (b == NULL) return 0;

	if (gm_cast<bool>(asrealpointer)) {
		// realpointer aka packed pointer (safe)
		static_assert((sizeof(double) >= sizeof(char*)), "realpointer size check fail.");
		double vv = 0.0;
		*reinterpret_cast<char**>(&vv) = b->GetData();
		return vv;
	}
	else {
		// cast pointer to double (UNSAFE!)
		// this is what window_handle() and get_function_address() in native GM do.
		return (double)((uintptr_t)b->GetData());
	}
}

static char ptrstringbuf[32];

gmexport const char* buffer_get_address_string(double id, double ashexstring) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if (b == NULL) return 0;

	// clear the buffer
	memset(&ptrstringbuf, 0, sizeof(ptrstringbuf));

	// get pointer as an unsigned pointer int.
	uintptr_t val = (uintptr_t)b->GetData();

	if (gm_cast<bool>(ashexstring)) {
		// as a hex string
		snprintf(ptrstringbuf, sizeof(ptrstringbuf) - 1, "%" PRIxPTR, val);
	}
	else {
		// uintptr_t to string
		snprintf(ptrstringbuf, sizeof(ptrstringbuf) - 1, "%" PRIuPTR, val);
	}

	return ptrstringbuf;
}


gmexport double buffer_peek(double id,double pos) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
    unsigned int oldpos = b->GetPos();
    b->SetPos(pos);
    double ret = b->ReadType<uint8_t>();
    b->SetPos(oldpos);
	return ret;
}

gmexport double buffer_poke(double id,double pos,double byte) {
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(id));
	if(b == NULL) return 0;
    unsigned int oldpos = b->GetPos();
    b->SetPos(pos);
    b->WriteType<uint8_t>(gm_cast<uint8_t>(byte));
    b->SetPos(oldpos);
	return 1;
}