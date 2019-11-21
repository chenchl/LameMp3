#include <jni.h>
#include <string>
#include "libmp3lame/lame.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_com_ccl_ndk_lamemp3_LameUtil_getVersion(JNIEnv *env, jclass clazz) {
    return env->NewStringUTF(get_lame_version());
}

const int BUFF_SIZE = 8192;
extern "C"
JNIEXPORT void JNICALL
Java_com_ccl_ndk_lamemp3_LameUtil_pcm2mp3withParm(JNIEnv *env, jclass clazz, jstring input_path,
                                                  jboolean is_wav, jstring mp3path, jint channel,
                                                  jint samplerate, jint brate, jint quality) {
    jboolean isCopy;
    const char *cinput = env->GetStringUTFChars(input_path, &isCopy);
    const char *cmp3 = env->GetStringUTFChars(mp3path, &isCopy);

    // 打开wav文件
    FILE *finput = fopen(cinput, "rb");

    if (is_wav) {// 移除wav文件头
        fseek(finput, 4 * 1024, SEEK_CUR);
    }

    FILE *fmp3 = fopen(cmp3, "wb+");

    short int wav_buffer[BUFF_SIZE * channel];
    unsigned char mp3_buffer[BUFF_SIZE];

    // init lame
    lame_global_flags *lameConvert;
    lameConvert = lame_init();

    lame_set_in_samplerate(lameConvert, samplerate);//采样率
    lame_set_num_channels(lameConvert, channel);//声道数
    lame_set_out_samplerate(lameConvert, samplerate);//采样率
    lame_set_brate(lameConvert, brate);//比特率
    lame_set_mode(lameConvert, MONO);//模式
    lame_set_quality(lameConvert, quality);//质量

    lame_set_VBR(lameConvert, vbr_default);
    lame_init_params(lameConvert);

    // start
    int read;
    int write;
    int total = 0;
    do {
        read = fread(wav_buffer, sizeof(short int) * channel, BUFF_SIZE, finput);
        total += read * sizeof(short int) * channel;
        if (read != 0) {
            write = lame_encode_buffer(lameConvert, wav_buffer, nullptr, read, mp3_buffer,
                                       BUFF_SIZE);
        } else {
            write = lame_encode_flush(lameConvert, mp3_buffer, BUFF_SIZE);
        }
        fwrite(mp3_buffer, 1, write, fmp3);

    } while (read != 0);
    lame_mp3_tags_fid(lameConvert, fmp3);//往mp3文件写入Xing VBR/INFO标签
    lame_close(lameConvert);//释放
    fclose(finput);
    fclose(fmp3);
    env->ReleaseStringUTFChars(input_path, cinput);
    env->ReleaseStringUTFChars(mp3path, cmp3);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_ccl_ndk_lamemp3_LameUtil_pcm2mp3(JNIEnv *env, jclass clazz, jstring input_path,
                                          jboolean is_wav, jstring mp3path) {
    Java_com_ccl_ndk_lamemp3_LameUtil_pcm2mp3withParm(env, clazz, input_path, is_wav, mp3path, 1,
                                                      16000, 16, 5);
}