
#include <jni.h>
#include <string>
#include <iostream>
#include "bay_pegops.h"

#include "pegops.h"

using namespace std;

static string jstring2string(JNIEnv *env, jstring jstr){
    const char *cstr = env->GetStringUTFChars(jstr, NULL);
    string cppstr = string(cstr);
    env->ReleaseStringUTFChars(jstr, cstr);
    return cppstr;
}

JNIEXPORT jobject JNICALL Java_bay_pegops_getpeglevel(
   JNIEnv *env, 
   jobject this_obj,

   jint     inp_cycle_now,
   jint     inp_cycle_prev, 
   jint     inp_peg_now, 
   jint     inp_peg_next, 
   jint     inp_peg_next_next,
   jstring  inp_exchange_pegdata64,
   jstring  inp_pegshift_pegdata64) {

   std::string    out_peglevel_hex;
   std::string    out_pegpool_pegdata64;
   std::string    out_err;

   bool ok = pegops::getpeglevel(
           inp_cycle_now,
           inp_cycle_prev,
           inp_peg_now,
           inp_peg_next,
           inp_peg_next_next,
           jstring2string(env, inp_exchange_pegdata64),
           jstring2string(env, inp_pegshift_pegdata64),
           
           out_peglevel_hex,
           out_pegpool_pegdata64,
           out_err);

   jclass      out_cls  = env->FindClass("bay/pegops$Out_getpeglevel");
   jmethodID   out_init = env->GetMethodID(out_cls, "<init>", "()V");
   jobject     out_obj  = env->NewObject(out_cls, out_init);

   jfieldID    out_ok_fid     = env->GetFieldID(out_cls, "out_ok", "Z");

   env->SetBooleanField(out_obj, out_ok_fid, ok);

   jfieldID    out_peglevel_hex_fid    = env->GetFieldID(out_cls, "out_peglevel_hex", "Ljava/lang/String;");
   jstring     out_peglevel_hex_jstr   = env->NewStringUTF(out_peglevel_hex.c_str());

   env->SetObjectField(out_obj, out_peglevel_hex_fid, out_peglevel_hex_jstr);

   jfieldID    out_pegpool_pegdata64_fid    = env->GetFieldID(out_cls, "out_pegpool_pegdata64", "Ljava/lang/String;");
   jstring     out_pegpool_pegdata64_jstr   = env->NewStringUTF(out_pegpool_pegdata64.c_str());

   env->SetObjectField(out_obj, out_pegpool_pegdata64_fid, out_pegpool_pegdata64_jstr);

   jfieldID    out_err_fid    = env->GetFieldID(out_cls, "out_err", "Ljava/lang/String;");
   jstring     out_err_jstr   = env->NewStringUTF(out_err.c_str());

   env->SetObjectField(out_obj, out_err_fid, out_err_jstr);

   return out_obj;
}

JNIEXPORT jobject JNICALL Java_bay_pegops_updatepegbalances(
   JNIEnv *env, 
   jobject this_obj,

   jstring inp_balance_pegdata64,
   jstring inp_pegpool_pegdata64,
   jstring inp_peglevel_hex) {

   std::string    out_balance_pegdata64;
   jlong          out_balance_liquid  =0;
   jlong          out_balance_reserve =0;
   std::string    out_pegpool_pegdata64;
   std::string    out_err;

   bool ok = pegops::updatepegbalances(
            jstring2string(env, inp_balance_pegdata64),
            jstring2string(env, inp_pegpool_pegdata64),
            jstring2string(env, inp_peglevel_hex),
           
            out_balance_pegdata64,
            out_balance_liquid,
            out_balance_reserve,
            out_pegpool_pegdata64,
            out_err);

   jclass      out_cls  = env->FindClass("bay/pegops$Out_updatepegbalances");
   jmethodID   out_init = env->GetMethodID(out_cls, "<init>", "()V");
   jobject     out_obj  = env->NewObject(out_cls, out_init);

   jfieldID    out_ok_fid     = env->GetFieldID(out_cls, "out_ok", "Z");
   env->SetBooleanField(out_obj, out_ok_fid, ok);

   jfieldID    out_balance_pegdata64_fid    = env->GetFieldID(out_cls, "out_balance_pegdata64", "Ljava/lang/String;");
   jstring     out_balance_pegdata64_jstr   = env->NewStringUTF(out_balance_pegdata64.c_str());
   env->SetObjectField(out_obj, out_balance_pegdata64_fid, out_balance_pegdata64_jstr);

   jfieldID    out_balance_liquid_fid    = env->GetFieldID(out_cls, "out_balance_liquid", "J");
   env->SetLongField(out_obj, out_balance_liquid_fid, out_balance_liquid);

   jfieldID    out_balance_reserve_fid    = env->GetFieldID(out_cls, "out_balance_reserve", "J");
   env->SetLongField(out_obj, out_balance_reserve_fid, out_balance_reserve);

   jfieldID    out_pegpool_pegdata64_fid    = env->GetFieldID(out_cls, "out_pegpool_pegdata64", "Ljava/lang/String;");
   jstring     out_pegpool_pegdata64_jstr   = env->NewStringUTF(out_pegpool_pegdata64.c_str());
   env->SetObjectField(out_obj, out_pegpool_pegdata64_fid, out_pegpool_pegdata64_jstr);

   jfieldID    out_err_fid    = env->GetFieldID(out_cls, "out_err", "Ljava/lang/String;");
   jstring     out_err_jstr   = env->NewStringUTF(out_err.c_str());
   env->SetObjectField(out_obj, out_err_fid, out_err_jstr);

   return out_obj;
}

JNIEXPORT jobject JNICALL Java_bay_pegops_movecoins(
   JNIEnv *env, 
   jobject this_obj,

   jlong    inp_move_amount,
   jstring  inp_src_pegdata64,
   jstring  inp_dst_pegdata64,
   jstring  inp_peglevel_hex,
   jboolean inp_cross_cycles) {

   std::string    out_src_pegdata64;
   int64_t        out_src_liquid    =0;
   int64_t        out_src_reserve   =0;
   std::string    out_dst_pegdata64;
   int64_t        out_dst_liquid    =0;
   int64_t        out_dst_reserve   =0;
   std::string    out_err;

   bool ok = pegops::movecoins(
            inp_move_amount,
            jstring2string(env, inp_src_pegdata64),
            jstring2string(env, inp_dst_pegdata64),
            jstring2string(env, inp_peglevel_hex),
            inp_cross_cycles,
           
            out_src_pegdata64,
            out_src_liquid,
            out_src_reserve,
            out_dst_pegdata64,
            out_dst_liquid,
            out_dst_reserve,
            out_err);

   jclass      out_cls  = env->FindClass("bay/pegops$Out_movecoins");
   jmethodID   out_init = env->GetMethodID(out_cls, "<init>", "()V");
   jobject     out_obj  = env->NewObject(out_cls, out_init);

   jfieldID    out_ok_fid     = env->GetFieldID(out_cls, "out_ok", "Z");
   env->SetBooleanField(out_obj, out_ok_fid, ok);

   jfieldID    out_src_pegdata64_fid    = env->GetFieldID(out_cls, "out_src_pegdata64", "Ljava/lang/String;");
   jstring     out_src_pegdata64_jstr   = env->NewStringUTF(out_src_pegdata64.c_str());
   env->SetObjectField(out_obj, out_src_pegdata64_fid, out_src_pegdata64_jstr);

   jfieldID    out_src_liquid_fid    = env->GetFieldID(out_cls, "out_src_liquid", "J");
   env->SetLongField(out_obj, out_src_liquid_fid, out_src_liquid);

   jfieldID    out_src_reserve_fid    = env->GetFieldID(out_cls, "out_src_reserve", "J");
   env->SetLongField(out_obj, out_src_reserve_fid, out_src_reserve);

   jfieldID    out_dst_pegdata64_fid    = env->GetFieldID(out_cls, "out_dst_pegdata64", "Ljava/lang/String;");
   jstring     out_dst_pegdata64_jstr   = env->NewStringUTF(out_dst_pegdata64.c_str());
   env->SetObjectField(out_obj, out_dst_pegdata64_fid, out_dst_pegdata64_jstr);

   jfieldID    out_dst_liquid_fid    = env->GetFieldID(out_cls, "out_dst_liquid", "J");
   env->SetLongField(out_obj, out_dst_liquid_fid, out_dst_liquid);

   jfieldID    out_dst_reserve_fid    = env->GetFieldID(out_cls, "out_dst_reserve", "J");
   env->SetLongField(out_obj, out_dst_reserve_fid, out_dst_reserve);

   jfieldID    out_err_fid    = env->GetFieldID(out_cls, "out_err", "Ljava/lang/String;");
   jstring     out_err_jstr   = env->NewStringUTF(out_err.c_str());
   env->SetObjectField(out_obj, out_err_fid, out_err_jstr);

   return out_obj;
}

JNIEXPORT jobject JNICALL Java_bay_pegops_moveliquid(
   JNIEnv *env, 
   jobject this_obj,

   jlong    inp_move_amount,
   jstring  inp_src_pegdata64,
   jstring  inp_dst_pegdata64,
   jstring  inp_peglevel_hex) {

   std::string    out_src_pegdata64;
   int64_t        out_src_liquid    =0;
   int64_t        out_src_reserve   =0;
   std::string    out_dst_pegdata64;
   int64_t        out_dst_liquid    =0;
   int64_t        out_dst_reserve   =0;
   std::string    out_err;

   bool ok = pegops::moveliquid(
            inp_move_amount,
            jstring2string(env, inp_src_pegdata64),
            jstring2string(env, inp_dst_pegdata64),
            jstring2string(env, inp_peglevel_hex),
           
            out_src_pegdata64,
            out_src_liquid,
            out_src_reserve,
            out_dst_pegdata64,
            out_dst_liquid,
            out_dst_reserve,
            out_err);

   jclass      out_cls  = env->FindClass("bay/pegops$Out_movecoins");
   jmethodID   out_init = env->GetMethodID(out_cls, "<init>", "()V");
   jobject     out_obj  = env->NewObject(out_cls, out_init);

   jfieldID    out_ok_fid     = env->GetFieldID(out_cls, "out_ok", "Z");
   env->SetBooleanField(out_obj, out_ok_fid, ok);

   jfieldID    out_src_pegdata64_fid    = env->GetFieldID(out_cls, "out_src_pegdata64", "Ljava/lang/String;");
   jstring     out_src_pegdata64_jstr   = env->NewStringUTF(out_src_pegdata64.c_str());
   env->SetObjectField(out_obj, out_src_pegdata64_fid, out_src_pegdata64_jstr);

   jfieldID    out_src_liquid_fid    = env->GetFieldID(out_cls, "out_src_liquid", "J");
   env->SetLongField(out_obj, out_src_liquid_fid, out_src_liquid);

   jfieldID    out_src_reserve_fid    = env->GetFieldID(out_cls, "out_src_reserve", "J");
   env->SetLongField(out_obj, out_src_reserve_fid, out_src_reserve);

   jfieldID    out_dst_pegdata64_fid    = env->GetFieldID(out_cls, "out_dst_pegdata64", "Ljava/lang/String;");
   jstring     out_dst_pegdata64_jstr   = env->NewStringUTF(out_dst_pegdata64.c_str());
   env->SetObjectField(out_obj, out_dst_pegdata64_fid, out_dst_pegdata64_jstr);

   jfieldID    out_dst_liquid_fid    = env->GetFieldID(out_cls, "out_dst_liquid", "J");
   env->SetLongField(out_obj, out_dst_liquid_fid, out_dst_liquid);

   jfieldID    out_dst_reserve_fid    = env->GetFieldID(out_cls, "out_dst_reserve", "J");
   env->SetLongField(out_obj, out_dst_reserve_fid, out_dst_reserve);

   jfieldID    out_err_fid    = env->GetFieldID(out_cls, "out_err", "Ljava/lang/String;");
   jstring     out_err_jstr   = env->NewStringUTF(out_err.c_str());
   env->SetObjectField(out_obj, out_err_fid, out_err_jstr);

   return out_obj;
}

JNIEXPORT jobject JNICALL Java_bay_pegops_movereserve(
   JNIEnv *env, 
   jobject this_obj,

   jlong    inp_move_amount,
   jstring  inp_src_pegdata64,
   jstring  inp_dst_pegdata64,
   jstring  inp_peglevel_hex) {

   std::string    out_src_pegdata64;
   int64_t        out_src_liquid    =0;
   int64_t        out_src_reserve   =0;
   std::string    out_dst_pegdata64;
   int64_t        out_dst_liquid    =0;
   int64_t        out_dst_reserve   =0;
   std::string    out_err;

   bool ok = pegops::movereserve(
            inp_move_amount,
            jstring2string(env, inp_src_pegdata64),
            jstring2string(env, inp_dst_pegdata64),
            jstring2string(env, inp_peglevel_hex),
           
            out_src_pegdata64,
            out_src_liquid,
            out_src_reserve,
            out_dst_pegdata64,
            out_dst_liquid,
            out_dst_reserve,
            out_err);

   jclass      out_cls  = env->FindClass("bay/pegops$Out_movecoins");
   jmethodID   out_init = env->GetMethodID(out_cls, "<init>", "()V");
   jobject     out_obj  = env->NewObject(out_cls, out_init);

   jfieldID    out_ok_fid     = env->GetFieldID(out_cls, "out_ok", "Z");
   env->SetBooleanField(out_obj, out_ok_fid, ok);

   jfieldID    out_src_pegdata64_fid    = env->GetFieldID(out_cls, "out_src_pegdata64", "Ljava/lang/String;");
   jstring     out_src_pegdata64_jstr   = env->NewStringUTF(out_src_pegdata64.c_str());
   env->SetObjectField(out_obj, out_src_pegdata64_fid, out_src_pegdata64_jstr);

   jfieldID    out_src_liquid_fid    = env->GetFieldID(out_cls, "out_src_liquid", "J");
   env->SetLongField(out_obj, out_src_liquid_fid, out_src_liquid);

   jfieldID    out_src_reserve_fid    = env->GetFieldID(out_cls, "out_src_reserve", "J");
   env->SetLongField(out_obj, out_src_reserve_fid, out_src_reserve);

   jfieldID    out_dst_pegdata64_fid    = env->GetFieldID(out_cls, "out_dst_pegdata64", "Ljava/lang/String;");
   jstring     out_dst_pegdata64_jstr   = env->NewStringUTF(out_dst_pegdata64.c_str());
   env->SetObjectField(out_obj, out_dst_pegdata64_fid, out_dst_pegdata64_jstr);

   jfieldID    out_dst_liquid_fid    = env->GetFieldID(out_cls, "out_dst_liquid", "J");
   env->SetLongField(out_obj, out_dst_liquid_fid, out_dst_liquid);

   jfieldID    out_dst_reserve_fid    = env->GetFieldID(out_cls, "out_dst_reserve", "J");
   env->SetLongField(out_obj, out_dst_reserve_fid, out_dst_reserve);

   jfieldID    out_err_fid    = env->GetFieldID(out_cls, "out_err", "Ljava/lang/String;");
   jstring     out_err_jstr   = env->NewStringUTF(out_err.c_str());
   env->SetObjectField(out_obj, out_err_fid, out_err_jstr);

   return out_obj;
}
