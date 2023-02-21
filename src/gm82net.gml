#define __gm82net_init
    globalvar __gm82net_cross_detect;


#define d3d_model_save_g3z
    ///d3d_model_save_g3z(model,filename)
    var __b;
    d3d_model_save(argument0,argument1)
    __b=buffer_create()
    buffer_load(__b,argument1)
    buffer_deflate(__b)
    buffer_save(__b,argument1)
    buffer_destroy(__b)
    return argument0


#define d3d_model_load_g3z
    ///d3d_model_load_g3z(model,filename)
    var __b;
    __b=buffer_create()
    buffer_load(__b,argument1)
    buffer_inflate(__b)    
    d3d_model_load(argument0,buffer_make_pipe(__b))
    buffer_destroy(__b)
    return argument0
//
//