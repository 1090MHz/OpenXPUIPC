// SPDX-License-Identifier: LGPL-3.0-or-later
// Thin caching wrapper around XPLMDataAccess
#pragma once

#include <XPLMDataAccess.h>
#include <unordered_map>
#include <string>

class DataRefCache {
public:
    XPLMDataRef find(const char* path) {
        auto it = cache_.find(path);
        if (it != cache_.end()) return it->second;
        XPLMDataRef ref = XPLMFindDataRef(path);
        cache_[path] = ref;
        return ref;
    }

    float    get_f(const char* p)             { auto r = find(p); return r ? XPLMGetDataf(r) : 0.0f; }
    int      get_i(const char* p)             { auto r = find(p); return r ? XPLMGetDatai(r) : 0; }
    double   get_d(const char* p)             { auto r = find(p); return r ? XPLMGetDatad(r) : 0.0; }
    float    get_vf(const char* p, int idx)   { auto r = find(p); float v = 0; if (r) XPLMGetDatavf(r, &v, idx, 1); return v; }
    int      get_vi(const char* p, int idx)   { auto r = find(p); int   v = 0; if (r) XPLMGetDatavi(r, &v, idx, 1); return v; }

    void     set_f(const char* p, float v)           { auto r = find(p); if (r) XPLMSetDataf(r, v); }
    void     set_i(const char* p, int v)             { auto r = find(p); if (r) XPLMSetDatai(r, v); }
    void     set_vf(const char* p, float v, int idx) { auto r = find(p); if (r) XPLMSetDatavf(r, &v, idx, 1); }
    void     set_vi(const char* p, int v, int idx)   { auto r = find(p); if (r) XPLMSetDatavi(r, &v, idx, 1); }

private:
    std::unordered_map<std::string, XPLMDataRef> cache_;
};
