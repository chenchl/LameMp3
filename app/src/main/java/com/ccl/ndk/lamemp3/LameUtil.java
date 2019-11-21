package com.ccl.ndk.lamemp3;

/**
 * created by hasee on 2019/11/20
 **/
public class LameUtil {
    static {
        System.loadLibrary("lamemp3");
    }

    public static final int QUALITY_LOW = 7;
    public static final int QUALITY_MIDDLE = 5;
    public static final int QUALITY_HIGH = 3;

    /**
     * 获取lame版本号
     *
     * @return
     */
    public static native String getVersion();

    /**
     * 默认转换 单声道 16比特 16000采样率 质量5
     *
     * @param inputPath
     * @param isWav
     * @param mp3path
     */
    public static native void pcm2mp3(String inputPath, boolean isWav, String mp3path);

    /**
     * 转换
     *
     * @param inputPath
     * @param isWav
     * @param mp3path
     * @param channel
     * @param samplerate
     * @param brate
     * @param quality
     */
    public static native void pcm2mp3withParm(String inputPath, boolean isWav, String mp3path, int channel, int samplerate, int brate, int quality);
}
