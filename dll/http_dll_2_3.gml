#define http_dll_init
var dllfile;
if is_string(argument0) then dllfile = argument0;
else dllfile = 'http_dll_2_3.dll';

global.define_buffer_create = external_define(dllfile,'buffer_create',dll_cdecl,ty_real,0);
global.define_buffer_destroy = external_define(dllfile,'buffer_destroy',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_exists = external_define(dllfile,'buffer_exists',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_to_string = external_define(dllfile,'buffer_to_string',dll_cdecl,ty_string,1,ty_real);
global.define_buffer_get_pos = external_define(dllfile,'buffer_get_pos',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_get_length = external_define(dllfile,'buffer_get_length',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_at_end = external_define(dllfile,'buffer_at_end',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_get_error = external_define(dllfile,'buffer_get_error',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_clear_error = external_define(dllfile,'buffer_clear_error',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_clear = external_define(dllfile,'buffer_clear',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_set_pos = external_define(dllfile,'buffer_set_pos',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_read_from_file = external_define(dllfile,'buffer_read_from_file',dll_cdecl,ty_real,2,ty_real,ty_string);
global.define_buffer_read_from_file_part = external_define(dllfile,'buffer_read_from_file_part',dll_cdecl,ty_real,4,ty_real,ty_string,ty_real,ty_real);
global.define_buffer_write_to_file = external_define(dllfile,'buffer_write_to_file',dll_cdecl,ty_real,2,ty_real,ty_string);
global.define_buffer_append_to_file = external_define(dllfile,'buffer_append_to_file',dll_cdecl,ty_real,2,ty_real,ty_string);
global.define_buffer_rc4_crypt = external_define(dllfile,'buffer_rc4_crypt',dll_cdecl,ty_real,2,ty_real,ty_string);
global.define_buffer_rc4_crypt_buffer = external_define(dllfile,'buffer_rc4_crypt_buffer',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_zlib_compress = external_define(dllfile,'buffer_zlib_compress',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_zlib_uncompress = external_define(dllfile,'buffer_zlib_uncompress',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_read_int8 = external_define(dllfile,'buffer_read_int8',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_read_uint8 = external_define(dllfile,'buffer_read_uint8',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_read_int16 = external_define(dllfile,'buffer_read_int16',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_read_uint16 = external_define(dllfile,'buffer_read_uint16',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_read_int32 = external_define(dllfile,'buffer_read_int32',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_read_uint32 = external_define(dllfile,'buffer_read_uint32',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_read_int64 = external_define(dllfile,'buffer_read_int64',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_read_uint64 = external_define(dllfile,'buffer_read_uint64',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_read_intv = external_define(dllfile,'buffer_read_intv',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_read_uintv = external_define(dllfile,'buffer_read_uintv',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_read_float32 = external_define(dllfile,'buffer_read_float32',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_read_float64 = external_define(dllfile,'buffer_read_float64',dll_cdecl,ty_real,1,ty_real);
global.define_buffer_write_int8 = external_define(dllfile,'buffer_write_int8',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_write_uint8 = external_define(dllfile,'buffer_write_uint8',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_write_int16 = external_define(dllfile,'buffer_write_int16',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_write_uint16 = external_define(dllfile,'buffer_write_uint16',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_write_int32 = external_define(dllfile,'buffer_write_int32',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_write_uint32 = external_define(dllfile,'buffer_write_uint32',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_write_int64 = external_define(dllfile,'buffer_write_int64',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_write_uint64 = external_define(dllfile,'buffer_write_uint64',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_write_intv = external_define(dllfile,'buffer_write_intv',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_write_uintv = external_define(dllfile,'buffer_write_uintv',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_write_float32 = external_define(dllfile,'buffer_write_float32',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_write_float64 = external_define(dllfile,'buffer_write_float64',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_read_string = external_define(dllfile,'buffer_read_string',dll_cdecl,ty_string,1,ty_real);
global.define_buffer_write_string = external_define(dllfile,'buffer_write_string',dll_cdecl,ty_real,2,ty_real,ty_string);
global.define_buffer_read_data = external_define(dllfile,'buffer_read_data',dll_cdecl,ty_string,2,ty_real,ty_real);
global.define_buffer_write_data = external_define(dllfile,'buffer_write_data',dll_cdecl,ty_real,2,ty_real,ty_string);
global.define_buffer_read_hex = external_define(dllfile,'buffer_read_hex',dll_cdecl,ty_string,2,ty_real,ty_real);
global.define_buffer_write_hex = external_define(dllfile,'buffer_write_hex',dll_cdecl,ty_real,2,ty_real,ty_string);
global.define_buffer_read_base64 = external_define(dllfile,'buffer_read_base64',dll_cdecl,ty_string,2,ty_real,ty_real);
global.define_buffer_write_base64 = external_define(dllfile,'buffer_write_base64',dll_cdecl,ty_real,2,ty_real,ty_string);
global.define_buffer_write_buffer = external_define(dllfile,'buffer_write_buffer',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_write_buffer_part = external_define(dllfile,'buffer_write_buffer_part',dll_cdecl,ty_real,4,ty_real,ty_real,ty_real,ty_real);
global.define_md5_begin = external_define(dllfile,'md5_begin',dll_cdecl,ty_real,0);
global.define_md5_end = external_define(dllfile,'md5_end',dll_cdecl,ty_real,0);
global.define_md5_read_file = external_define(dllfile,'md5_read_file',dll_cdecl,ty_real,1,ty_string);
global.define_md5_read_string = external_define(dllfile,'md5_read_string',dll_cdecl,ty_real,1,ty_string);
global.define_md5_read_buffer = external_define(dllfile,'md5_read_buffer',dll_cdecl,ty_real,1,ty_real);
global.define_md5_read_buffer_part = external_define(dllfile,'md5_read_buffer_part',dll_cdecl,ty_real,3,ty_real,ty_real,ty_real);
global.define_md5_result = external_define(dllfile,'md5_result',dll_cdecl,ty_string,0);
global.define_sha1_begin = external_define(dllfile,'sha1_begin',dll_cdecl,ty_real,0);
global.define_sha1_end = external_define(dllfile,'sha1_end',dll_cdecl,ty_real,0);
global.define_sha1_read_file = external_define(dllfile,'sha1_read_file',dll_cdecl,ty_real,1,ty_string);
global.define_sha1_read_string = external_define(dllfile,'sha1_read_string',dll_cdecl,ty_real,1,ty_string);
global.define_sha1_read_buffer = external_define(dllfile,'sha1_read_buffer',dll_cdecl,ty_real,1,ty_real);
global.define_sha1_read_buffer_part = external_define(dllfile,'sha1_read_buffer_part',dll_cdecl,ty_real,3,ty_real,ty_real,ty_real);
global.define_sha1_result = external_define(dllfile,'sha1_result',dll_cdecl,ty_string,0);
global.define_listeningsocket_create = external_define(dllfile,'listeningsocket_create',dll_cdecl,ty_real,0);
global.define_listeningsocket_destroy = external_define(dllfile,'listeningsocket_destroy',dll_cdecl,ty_real,1,ty_real);
global.define_listeningsocket_exists = external_define(dllfile,'listeningsocket_exists',dll_cdecl,ty_real,1,ty_real);
global.define_listeningsocket_is_listening = external_define(dllfile,'listeningsocket_is_listening',dll_cdecl,ty_real,1,ty_real);
global.define_listeningsocket_start_listening = external_define(dllfile,'listeningsocket_start_listening',dll_cdecl,ty_real,4,ty_real,ty_real,ty_real,ty_real);
global.define_listeningsocket_stop_listening = external_define(dllfile,'listeningsocket_stop_listening',dll_cdecl,ty_real,1,ty_real);
global.define_listeningsocket_can_accept = external_define(dllfile,'listeningsocket_can_accept',dll_cdecl,ty_real,1,ty_real);
global.define_listeningsocket_accept = external_define(dllfile,'listeningsocket_accept',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_socket_create = external_define(dllfile,'socket_create',dll_cdecl,ty_real,0);
global.define_socket_destroy = external_define(dllfile,'socket_destroy',dll_cdecl,ty_real,1,ty_real);
global.define_socket_exists = external_define(dllfile,'socket_exists',dll_cdecl,ty_real,1,ty_real);
global.define_socket_get_state = external_define(dllfile,'socket_get_state',dll_cdecl,ty_real,1,ty_real);
global.define_socket_reset = external_define(dllfile,'socket_reset',dll_cdecl,ty_real,1,ty_real);
global.define_socket_connect = external_define(dllfile,'socket_connect',dll_cdecl,ty_real,3,ty_real,ty_string,ty_real);
global.define_socket_update_read = external_define(dllfile,'socket_update_read',dll_cdecl,ty_real,1,ty_real);
global.define_socket_update_write = external_define(dllfile,'socket_update_write',dll_cdecl,ty_real,1,ty_real);
global.define_socket_shut_down = external_define(dllfile,'socket_shut_down',dll_cdecl,ty_real,1,ty_real);
global.define_socket_get_peer_address = external_define(dllfile,'socket_get_peer_address',dll_cdecl,ty_string,1,ty_real);
global.define_socket_read_data = external_define(dllfile,'socket_read_data',dll_cdecl,ty_real,3,ty_real,ty_real,ty_real);
global.define_socket_write_data = external_define(dllfile,'socket_write_data',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_socket_read_message = external_define(dllfile,'socket_read_message',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_socket_write_message = external_define(dllfile,'socket_write_message',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_socket_read_message_delimiter = external_define(dllfile,'socket_read_message_delimiter',dll_cdecl,ty_real,3,ty_real,ty_real,ty_string);
global.define_socket_write_message_delimiter = external_define(dllfile,'socket_write_message_delimiter',dll_cdecl,ty_real,3,ty_real,ty_real,ty_string);
global.define_socket_get_read_data_length = external_define(dllfile,'socket_get_read_data_length',dll_cdecl,ty_real,1,ty_real);
global.define_socket_get_write_data_length = external_define(dllfile,'socket_get_write_data_length',dll_cdecl,ty_real,1,ty_real);
global.define_udpsocket_create = external_define(dllfile,'udpsocket_create',dll_cdecl,ty_real,0);
global.define_udpsocket_destroy = external_define(dllfile,'udpsocket_destroy',dll_cdecl,ty_real,1,ty_real);
global.define_udpsocket_exists = external_define(dllfile,'udpsocket_exists',dll_cdecl,ty_real,1,ty_real);
global.define_udpsocket_get_state = external_define(dllfile,'udpsocket_get_state',dll_cdecl,ty_real,1,ty_real);
global.define_udpsocket_reset = external_define(dllfile,'udpsocket_reset',dll_cdecl,ty_real,1,ty_real);
global.define_udpsocket_start = external_define(dllfile,'udpsocket_start',dll_cdecl,ty_real,3,ty_real,ty_real,ty_real);
global.define_udpsocket_set_destination = external_define(dllfile,'udpsocket_set_destination',dll_cdecl,ty_real,3,ty_real,ty_string,ty_real);
global.define_udpsocket_receive = external_define(dllfile,'udpsocket_receive',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_udpsocket_send = external_define(dllfile,'udpsocket_send',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_udpsocket_get_last_address = external_define(dllfile,'udpsocket_get_last_address',dll_cdecl,ty_string,1,ty_real);
global.define_udpsocket_get_last_port = external_define(dllfile,'udpsocket_get_last_port',dll_cdecl,ty_real,1,ty_real);
global.define_udpsocket_get_max_message_size = external_define(dllfile,'udpsocket_get_max_message_size',dll_cdecl,ty_real,1,ty_real);
global.define_httprequest_create = external_define(dllfile,'httprequest_create',dll_cdecl,ty_real,0);
global.define_httprequest_destroy = external_define(dllfile,'httprequest_destroy',dll_cdecl,ty_real,1,ty_real);
global.define_httprequest_exists = external_define(dllfile,'httprequest_exists',dll_cdecl,ty_real,1,ty_real);
global.define_httprequest_get_state = external_define(dllfile,'httprequest_get_state',dll_cdecl,ty_real,1,ty_real);
global.define_httprequest_set_request_header = external_define(dllfile,'httprequest_set_request_header',dll_cdecl,ty_real,4,ty_real,ty_string,ty_string,ty_real);
global.define_httprequest_remove_request_header = external_define(dllfile,'httprequest_remove_request_header',dll_cdecl,ty_real,2,ty_real,ty_string);
global.define_httprequest_clear_request_headers = external_define(dllfile,'httprequest_clear_request_headers',dll_cdecl,ty_real,1,ty_real);
global.define_httprequest_set_post_parameter = external_define(dllfile,'httprequest_set_post_parameter',dll_cdecl,ty_real,3,ty_real,ty_string,ty_string);
global.define_httprequest_set_post_parameter_file = external_define(dllfile,'httprequest_set_post_parameter_file',dll_cdecl,ty_real,4,ty_real,ty_string,ty_string,ty_real);
global.define_httprequest_remove_post_parameter = external_define(dllfile,'httprequest_remove_post_parameter',dll_cdecl,ty_real,2,ty_real,ty_string);
global.define_httprequest_clear_post_parameters = external_define(dllfile,'httprequest_clear_post_parameters',dll_cdecl,ty_real,1,ty_real);
global.define_httprequest_reset = external_define(dllfile,'httprequest_reset',dll_cdecl,ty_real,1,ty_real);
global.define_httprequest_connect = external_define(dllfile,'httprequest_connect',dll_cdecl,ty_real,3,ty_real,ty_string,ty_real);
global.define_httprequest_update = external_define(dllfile,'httprequest_update',dll_cdecl,ty_real,1,ty_real);
global.define_httprequest_get_status_code = external_define(dllfile,'httprequest_get_status_code',dll_cdecl,ty_real,1,ty_real);
global.define_httprequest_get_response_header_count = external_define(dllfile,'httprequest_get_response_header_count',dll_cdecl,ty_real,1,ty_real);
global.define_httprequest_get_response_header_name = external_define(dllfile,'httprequest_get_response_header_name',dll_cdecl,ty_string,2,ty_real,ty_real);
global.define_httprequest_get_response_header_value = external_define(dllfile,'httprequest_get_response_header_value',dll_cdecl,ty_string,2,ty_real,ty_real);
global.define_httprequest_find_response_header = external_define(dllfile,'httprequest_find_response_header',dll_cdecl,ty_string,2,ty_real,ty_string);
global.define_httprequest_get_message_body = external_define(dllfile,'httprequest_get_message_body',dll_cdecl,ty_string,1,ty_real);
global.define_httprequest_get_message_body_length = external_define(dllfile,'httprequest_get_message_body_length',dll_cdecl,ty_real,1,ty_real);
global.define_httprequest_get_message_body_buffer = external_define(dllfile,'httprequest_get_message_body_buffer',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_httprequest_urlencode = external_define(dllfile,'httprequest_urlencode',dll_cdecl,ty_string,2,ty_string,ty_real);
global.define_httprequest_urldecode = external_define(dllfile,'httprequest_urldecode',dll_cdecl,ty_string,1,ty_string);
global.define_buffer_get_address = external_define(dllfile,'buffer_get_address',dll_cdecl,ty_real,2,ty_real,ty_real);
global.define_buffer_get_address_string = external_define(dllfile,'buffer_get_address_string',dll_cdecl,ty_string,2,ty_real,ty_real);

#define buffer_create
// buffer_create()
return external_call(global.define_buffer_create);
#define buffer_destroy
// buffer_destroy(id)
return external_call(global.define_buffer_destroy,argument0);
#define buffer_exists
// buffer_exists(id)
return external_call(global.define_buffer_exists,argument0);
#define buffer_to_string
// buffer_to_string(id)
return external_call(global.define_buffer_to_string,argument0);
#define buffer_get_pos
// buffer_get_pos(id)
return external_call(global.define_buffer_get_pos,argument0);
#define buffer_get_length
// buffer_get_length(id)
return external_call(global.define_buffer_get_length,argument0);
#define buffer_at_end
// buffer_at_end(id)
return external_call(global.define_buffer_at_end,argument0);
#define buffer_get_error
// buffer_get_error(id)
return external_call(global.define_buffer_get_error,argument0);
#define buffer_clear_error
// buffer_clear_error(id)
return external_call(global.define_buffer_clear_error,argument0);
#define buffer_clear
// buffer_clear(id)
return external_call(global.define_buffer_clear,argument0);
#define buffer_set_pos
// buffer_set_pos(id,pos)
return external_call(global.define_buffer_set_pos,argument0,argument1);
#define buffer_read_from_file
// buffer_read_from_file(id,filename)
return external_call(global.define_buffer_read_from_file,argument0,argument1);
#define buffer_read_from_file_part
// buffer_read_from_file_part(id,filename,pos,len)
return external_call(global.define_buffer_read_from_file_part,argument0,argument1,argument2,argument3);
#define buffer_write_to_file
// buffer_write_to_file(id,filename)
return external_call(global.define_buffer_write_to_file,argument0,argument1);
#define buffer_append_to_file
// buffer_append_to_file(id,filename)
return external_call(global.define_buffer_append_to_file,argument0,argument1);
#define buffer_rc4_crypt
// buffer_rc4_crypt(id,key)
return external_call(global.define_buffer_rc4_crypt,argument0,argument1);
#define buffer_rc4_crypt_buffer
// buffer_rc4_crypt_buffer(id,id2)
return external_call(global.define_buffer_rc4_crypt_buffer,argument0,argument1);
#define buffer_zlib_compress
// buffer_zlib_compress(id)
return external_call(global.define_buffer_zlib_compress,argument0);
#define buffer_zlib_uncompress
// buffer_zlib_uncompress(id)
return external_call(global.define_buffer_zlib_uncompress,argument0);
#define buffer_read_int8
// buffer_read_int8(id)
return external_call(global.define_buffer_read_int8,argument0);
#define buffer_read_uint8
// buffer_read_uint8(id)
return external_call(global.define_buffer_read_uint8,argument0);
#define buffer_read_int16
// buffer_read_int16(id)
return external_call(global.define_buffer_read_int16,argument0);
#define buffer_read_uint16
// buffer_read_uint16(id)
return external_call(global.define_buffer_read_uint16,argument0);
#define buffer_read_int32
// buffer_read_int32(id)
return external_call(global.define_buffer_read_int32,argument0);
#define buffer_read_uint32
// buffer_read_uint32(id)
return external_call(global.define_buffer_read_uint32,argument0);
#define buffer_read_int64
// buffer_read_int64(id)
return external_call(global.define_buffer_read_int64,argument0);
#define buffer_read_uint64
// buffer_read_uint64(id)
return external_call(global.define_buffer_read_uint64,argument0);
#define buffer_read_intv
// buffer_read_intv(id)
return external_call(global.define_buffer_read_intv,argument0);
#define buffer_read_uintv
// buffer_read_uintv(id)
return external_call(global.define_buffer_read_uintv,argument0);
#define buffer_read_float32
// buffer_read_float32(id)
return external_call(global.define_buffer_read_float32,argument0);
#define buffer_read_float64
// buffer_read_float64(id)
return external_call(global.define_buffer_read_float64,argument0);
#define buffer_write_int8
// buffer_write_int8(id,value)
return external_call(global.define_buffer_write_int8,argument0,argument1);
#define buffer_write_uint8
// buffer_write_uint8(id,value)
return external_call(global.define_buffer_write_uint8,argument0,argument1);
#define buffer_write_int16
// buffer_write_int16(id,value)
return external_call(global.define_buffer_write_int16,argument0,argument1);
#define buffer_write_uint16
// buffer_write_uint16(id,value)
return external_call(global.define_buffer_write_uint16,argument0,argument1);
#define buffer_write_int32
// buffer_write_int32(id,value)
return external_call(global.define_buffer_write_int32,argument0,argument1);
#define buffer_write_uint32
// buffer_write_uint32(id,value)
return external_call(global.define_buffer_write_uint32,argument0,argument1);
#define buffer_write_int64
// buffer_write_int64(id,value)
return external_call(global.define_buffer_write_int64,argument0,argument1);
#define buffer_write_uint64
// buffer_write_uint64(id,value)
return external_call(global.define_buffer_write_uint64,argument0,argument1);
#define buffer_write_intv
// buffer_write_intv(id,value)
return external_call(global.define_buffer_write_intv,argument0,argument1);
#define buffer_write_uintv
// buffer_write_uintv(id,value)
return external_call(global.define_buffer_write_uintv,argument0,argument1);
#define buffer_write_float32
// buffer_write_float32(id,value)
return external_call(global.define_buffer_write_float32,argument0,argument1);
#define buffer_write_float64
// buffer_write_float64(id,value)
return external_call(global.define_buffer_write_float64,argument0,argument1);
#define buffer_read_string
// buffer_read_string(id)
return external_call(global.define_buffer_read_string,argument0);
#define buffer_write_string
// buffer_write_string(id,string)
return external_call(global.define_buffer_write_string,argument0,argument1);
#define buffer_read_data
// buffer_read_data(id,len)
return external_call(global.define_buffer_read_data,argument0,argument1);
#define buffer_write_data
// buffer_write_data(id,string)
return external_call(global.define_buffer_write_data,argument0,argument1);
#define buffer_read_hex
// buffer_read_hex(id,len)
return external_call(global.define_buffer_read_hex,argument0,argument1);
#define buffer_write_hex
// buffer_write_hex(id,string)
return external_call(global.define_buffer_write_hex,argument0,argument1);
#define buffer_read_base64
// buffer_read_base64(id,len)
return external_call(global.define_buffer_read_base64,argument0,argument1);
#define buffer_write_base64
// buffer_write_base64(id,string)
return external_call(global.define_buffer_write_base64,argument0,argument1);
#define buffer_write_buffer
// buffer_write_buffer(id,id2)
return external_call(global.define_buffer_write_buffer,argument0,argument1);
#define buffer_write_buffer_part
// buffer_write_buffer_part(id,id2,pos,len)
return external_call(global.define_buffer_write_buffer_part,argument0,argument1,argument2,argument3);
#define md5_begin
// md5_begin()
return external_call(global.define_md5_begin);
#define md5_end
// md5_end()
return external_call(global.define_md5_end);
#define md5_read_file
// md5_read_file(filename)
return external_call(global.define_md5_read_file,argument0);
#define md5_read_string
// md5_read_string(string)
return external_call(global.define_md5_read_string,argument0);
#define md5_read_buffer
// md5_read_buffer(id)
return external_call(global.define_md5_read_buffer,argument0);
#define md5_read_buffer_part
// md5_read_buffer_part(id,pos,len)
return external_call(global.define_md5_read_buffer_part,argument0,argument1,argument2);
#define md5_result
// md5_result()
return external_call(global.define_md5_result);
#define sha1_begin
// sha1_begin()
return external_call(global.define_sha1_begin);
#define sha1_end
// sha1_end()
return external_call(global.define_sha1_end);
#define sha1_read_file
// sha1_read_file(filename)
return external_call(global.define_sha1_read_file,argument0);
#define sha1_read_string
// sha1_read_string(string)
return external_call(global.define_sha1_read_string,argument0);
#define sha1_read_buffer
// sha1_read_buffer(id)
return external_call(global.define_sha1_read_buffer,argument0);
#define sha1_read_buffer_part
// sha1_read_buffer_part(id,pos,len)
return external_call(global.define_sha1_read_buffer_part,argument0,argument1,argument2);
#define sha1_result
// sha1_result()
return external_call(global.define_sha1_result);
#define listeningsocket_create
// listeningsocket_create()
return external_call(global.define_listeningsocket_create);
#define listeningsocket_destroy
// listeningsocket_destroy(id)
return external_call(global.define_listeningsocket_destroy,argument0);
#define listeningsocket_exists
// listeningsocket_exists(id)
return external_call(global.define_listeningsocket_exists,argument0);
#define listeningsocket_is_listening
// listeningsocket_is_listening(id)
return external_call(global.define_listeningsocket_is_listening,argument0);
#define listeningsocket_start_listening
// listeningsocket_start_listening(id,ipv6,port,local)
return external_call(global.define_listeningsocket_start_listening,argument0,argument1,argument2,argument3);
#define listeningsocket_stop_listening
// listeningsocket_stop_listening(id)
return external_call(global.define_listeningsocket_stop_listening,argument0);
#define listeningsocket_can_accept
// listeningsocket_can_accept(id)
return external_call(global.define_listeningsocket_can_accept,argument0);
#define listeningsocket_accept
// listeningsocket_accept(id,socket_id)
return external_call(global.define_listeningsocket_accept,argument0,argument1);
#define socket_create
// socket_create()
return external_call(global.define_socket_create);
#define socket_destroy
// socket_destroy(id)
return external_call(global.define_socket_destroy,argument0);
#define socket_exists
// socket_exists(id)
return external_call(global.define_socket_exists,argument0);
#define socket_get_state
// socket_get_state(id)
return external_call(global.define_socket_get_state,argument0);
#define socket_reset
// socket_reset(id)
return external_call(global.define_socket_reset,argument0);
#define socket_connect
// socket_connect(id,address,port)
return external_call(global.define_socket_connect,argument0,argument1,argument2);
#define socket_update_read
// socket_update_read(id)
return external_call(global.define_socket_update_read,argument0);
#define socket_update_write
// socket_update_write(id)
return external_call(global.define_socket_update_write,argument0);
#define socket_shut_down
// socket_shut_down(id)
return external_call(global.define_socket_shut_down,argument0);
#define socket_get_peer_address
// socket_get_peer_address(id)
return external_call(global.define_socket_get_peer_address,argument0);
#define socket_read_data
// socket_read_data(id,buffer_id,bytes)
return external_call(global.define_socket_read_data,argument0,argument1,argument2);
#define socket_write_data
// socket_write_data(id,buffer_id)
return external_call(global.define_socket_write_data,argument0,argument1);
#define socket_read_message
// socket_read_message(id,buffer_id)
return external_call(global.define_socket_read_message,argument0,argument1);
#define socket_write_message
// socket_write_message(id,buffer_id)
return external_call(global.define_socket_write_message,argument0,argument1);
#define socket_read_message_delimiter
// socket_read_message_delimiter(id,buffer_id,delimiter)
return external_call(global.define_socket_read_message_delimiter,argument0,argument1,argument2);
#define socket_write_message_delimiter
// socket_write_message_delimiter(id,buffer_id,delimiter)
return external_call(global.define_socket_write_message_delimiter,argument0,argument1,argument2);
#define socket_get_read_data_length
// socket_get_read_data_length(id)
return external_call(global.define_socket_get_read_data_length,argument0);
#define socket_get_write_data_length
// socket_get_write_data_length(id)
return external_call(global.define_socket_get_write_data_length,argument0);
#define udpsocket_create
// udpsocket_create()
return external_call(global.define_udpsocket_create);
#define udpsocket_destroy
// udpsocket_destroy(id)
return external_call(global.define_udpsocket_destroy,argument0);
#define udpsocket_exists
// udpsocket_exists(id)
return external_call(global.define_udpsocket_exists,argument0);
#define udpsocket_get_state
// udpsocket_get_state(id)
return external_call(global.define_udpsocket_get_state,argument0);
#define udpsocket_reset
// udpsocket_reset(id)
return external_call(global.define_udpsocket_reset,argument0);
#define udpsocket_start
// udpsocket_start(id,ipv6,port)
return external_call(global.define_udpsocket_start,argument0,argument1,argument2);
#define udpsocket_set_destination
// udpsocket_set_destination(id,address,port)
return external_call(global.define_udpsocket_set_destination,argument0,argument1,argument2);
#define udpsocket_receive
// udpsocket_receive(id,buffer_id)
return external_call(global.define_udpsocket_receive,argument0,argument1);
#define udpsocket_send
// udpsocket_send(id,buffer_id)
return external_call(global.define_udpsocket_send,argument0,argument1);
#define udpsocket_get_last_address
// udpsocket_get_last_address(id)
return external_call(global.define_udpsocket_get_last_address,argument0);
#define udpsocket_get_last_port
// udpsocket_get_last_port(id)
return external_call(global.define_udpsocket_get_last_port,argument0);
#define udpsocket_get_max_message_size
// udpsocket_get_max_message_size(id)
return external_call(global.define_udpsocket_get_max_message_size,argument0);
#define httprequest_create
// httprequest_create()
return external_call(global.define_httprequest_create);
#define httprequest_destroy
// httprequest_destroy(id)
return external_call(global.define_httprequest_destroy,argument0);
#define httprequest_exists
// httprequest_exists(id)
return external_call(global.define_httprequest_exists,argument0);
#define httprequest_get_state
// httprequest_get_state(id)
return external_call(global.define_httprequest_get_state,argument0);
#define httprequest_set_request_header
// httprequest_set_request_header(id,name,value,replace)
return external_call(global.define_httprequest_set_request_header,argument0,argument1,argument2,argument3);
#define httprequest_remove_request_header
// httprequest_remove_request_header(id,name)
return external_call(global.define_httprequest_remove_request_header,argument0,argument1);
#define httprequest_clear_request_headers
// httprequest_clear_request_headers(id)
return external_call(global.define_httprequest_clear_request_headers,argument0);
#define httprequest_set_post_parameter
// httprequest_set_post_parameter(id,name,value)
return external_call(global.define_httprequest_set_post_parameter,argument0,argument1,argument2);
#define httprequest_set_post_parameter_file
// httprequest_set_post_parameter_file(id,name,filename,buffer_id)
return external_call(global.define_httprequest_set_post_parameter_file,argument0,argument1,argument2,argument3);
#define httprequest_remove_post_parameter
// httprequest_remove_post_parameter(id,name)
return external_call(global.define_httprequest_remove_post_parameter,argument0,argument1);
#define httprequest_clear_post_parameters
// httprequest_clear_post_parameters(id)
return external_call(global.define_httprequest_clear_post_parameters,argument0);
#define httprequest_reset
// httprequest_reset(id)
return external_call(global.define_httprequest_reset,argument0);
#define httprequest_connect
// httprequest_connect(id,url,post)
return external_call(global.define_httprequest_connect,argument0,argument1,argument2);
#define httprequest_update
// httprequest_update(id)
return external_call(global.define_httprequest_update,argument0);
#define httprequest_get_status_code
// httprequest_get_status_code(id)
return external_call(global.define_httprequest_get_status_code,argument0);
#define httprequest_get_response_header_count
// httprequest_get_response_header_count(id)
return external_call(global.define_httprequest_get_response_header_count,argument0);
#define httprequest_get_response_header_name
// httprequest_get_response_header_name(id,index)
return external_call(global.define_httprequest_get_response_header_name,argument0,argument1);
#define httprequest_get_response_header_value
// httprequest_get_response_header_value(id,index)
return external_call(global.define_httprequest_get_response_header_value,argument0,argument1);
#define httprequest_find_response_header
// httprequest_find_response_header(id,name)
return external_call(global.define_httprequest_find_response_header,argument0,argument1);
#define httprequest_get_message_body
// httprequest_get_message_body(id)
return external_call(global.define_httprequest_get_message_body,argument0);
#define httprequest_get_message_body_length
// httprequest_get_message_body_length(id)
return external_call(global.define_httprequest_get_message_body_length,argument0);
#define httprequest_get_message_body_buffer
// httprequest_get_message_body_buffer(id,buffer_id)
return external_call(global.define_httprequest_get_message_body_buffer,argument0,argument1);
#define httprequest_urlencode
// httprequest_urlencode(string,keepspecialchars)
return external_call(global.define_httprequest_urlencode,argument0,argument1);
#define httprequest_urldecode
// httprequest_urldecode(string)
return external_call(global.define_httprequest_urldecode,argument0);
#define buffer_get_address
// buffer_get_address(id,asrealpointer)
return external_call(global.define_buffer_get_address,argument0,argument1);
#define buffer_get_address_string
// buffer_get_address_string(id,ashexstring)
return external_call(global.define_buffer_get_address_string,argument0,argument1);
