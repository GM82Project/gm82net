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

gmexport double httprequest_create() {
	HttpRequest *hr = NULL; // GCC is complaining for some reason ...
	hr = new HttpRequest();
	try {
		gmdata.httprequests.insert(std::pair<unsigned int, HttpRequest*>(++gmdata.idcounter_httprequests, hr));
	}
	catch(...) {
		delete hr;
		throw;
	}
	return gmdata.idcounter_httprequests;
}

gmexport double httprequest_destroy(double id) {
	std::map<unsigned int, HttpRequest*>::iterator it = gmdata.httprequests.find(gm_cast<unsigned int>(id));
	if(it == gmdata.httprequests.end()) {
		return 0;
	}
	delete it->second;
	gmdata.httprequests.erase(it);
	return 1;
}

gmexport double httprequest_exists(double id) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	return (hr == NULL)? 0 : 1;
}

gmexport double httprequest_get_state(double id) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	return hr->GetState();
}

gmexport double httprequest_set_request_header(double id, const char* name, const char* value, double replace) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	hr->SetRequestHeader(name, value, gm_cast<bool>(replace));
	return 1;
}

gmexport double httprequest_remove_request_header(double id, const char* name) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	hr->RemoveRequestHeader(name);
	return 1;
}

gmexport double httprequest_clear_request_headers(double id) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	hr->ClearRequestHeaders();
	return 1;
}

gmexport double httprequest_set_post_parameter(double id, const char* name, const char* value) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	hr->SetPostParameter(name, value);
	return 1;
}

gmexport double httprequest_set_post_parameter_file(double id, const char* name, const char* filename, double buffer_id) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
	if(b == NULL) return 0;
	hr->SetPostParameterFile(name, filename, std::string(b->GetData(), b->GetLength()));
	return 1;
}

gmexport double httprequest_remove_post_parameter(double id, const char* name) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	hr->RemovePostParameter(name);
	return 1;
}

gmexport double httprequest_clear_post_parameters(double id) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	hr->ClearPostParameters();
	return 1;
}

gmexport double httprequest_reset(double id) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	hr->Reset();
	return 1;
}

gmexport double httprequest_connect(double id, const char* url, double post) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	hr->Connect(url, gm_cast<bool>(post));
	return 1;
}

gmexport double httprequest_update(double id) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	hr->Update();
	return 1;
}

gmexport double httprequest_get_status_code(double id) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	return hr->GetStatusCode();
}

gmexport double httprequest_get_response_header_count(double id) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	return hr->GetResponseHeaderCount();
}

gmexport const char* httprequest_get_response_header_name(double id, double index) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return "";
	gmreturnstring = hr->GetResponseHeaderName(gm_cast<unsigned int>(index));
	return gmreturnstring.c_str();
}

gmexport const char* httprequest_get_response_header_value(double id, double index) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return "";
	gmreturnstring = hr->GetResponseHeaderValue(gm_cast<unsigned int>(index));
	return gmreturnstring.c_str();
}

gmexport const char* httprequest_find_response_header(double id, const char* name) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return "";
	gmreturnstring = hr->FindResponseHeader(name);
	return gmreturnstring.c_str();
}

gmexport const char* httprequest_get_message_body(double id) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return "";
	gmreturnstring.assign(hr->GetMessageBody(), hr->GetMessageBodyLength());
	return gmreturnstring.c_str();
}

gmexport double httprequest_get_message_body_length(double id) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	return hr->GetMessageBodyLength();
}

gmexport double httprequest_get_message_body_buffer(double id, double buffer_id) {
	HttpRequest *hr = gmdata.FindHttpRequest(gm_cast<unsigned int>(id));
	if(hr == NULL) return 0;
	Buffer *b = gmdata.FindBuffer(gm_cast<unsigned int>(buffer_id));
	if(b == NULL) return 0;
	unsigned int l = hr->GetMessageBodyLength();
	b->Clear();
	if(l != 0) {
		b->SetLength(l);
		memcpy(b->GetData(), hr->GetMessageBody(), l);
	}
	return 1;
}

gmexport const char* httprequest_urlencode(const char* string, double keepspecialchars) {
	gmreturnstring = HttpRequest::UrlEncode(string, gm_cast<bool>(keepspecialchars));
	return gmreturnstring.c_str();
}

gmexport const char* httprequest_urldecode(const char* string) {
	gmreturnstring = HttpRequest::UrlDecode(string);
	return gmreturnstring.c_str();
}
