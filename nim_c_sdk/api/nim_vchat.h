﻿/** @file nim_vchat.h
  * @brief NIM VChat提供的音视频相关接口
  * @copyright (c) 2015-2016, NetEase Inc. All rights reserved
  * @author gq
  * @date 2015/4/30
  */

#ifndef NIM_SDK_DLL_API_NIM_VCHAT_H_
#define NIM_SDK_DLL_API_NIM_VCHAT_H_

#include "nim_sdk_dll.h"
#include "nim_vchat_def.h"

#ifdef __cplusplus
extern"C"
{
#endif
/** @fn bool nim_vchat_init(const char *json_extension) 
  * NIM VCHAT初始化，需要在SDK的nim_client_init成功之后
  * @param[in] json_extension 无效的扩展字段
  * @return bool 初始化结果，如果是false则以下所有接口调用无效
  */ 
NIM_SDK_DLL_API	bool nim_vchat_init(const char *json_extension);

/** @fn bool nim_vchat_cleanup(const char *json_extension) 
  * NIM VCHAT清理，需要在SDK的nim_client_cleanup之前
  * @param[in] json_extension 无效的扩展字段
  * @return void 无返回值
  */ 
NIM_SDK_DLL_API	void nim_vchat_cleanup(const char *json_extension);

//通话相关

/** @fn void nim_vchat_set_cb_func(nim_vchat_cb_func cb, const void *user_data)
  * NIM VCHAT 设置通话回调或者服务器通知
  * @param[in] cb 结果回调见nim_vchat_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_vchat_set_cb_func(nim_vchat_cb_func cb, const void *user_data);

/** @fn bool nim_vchat_start(NIMVideoChatMode mode, const char *apns_text, const char *custom_info, const char *json_extension, const void *user_data)
  * NIM VCHAT 启动点对点通话，异步回调nim_vchat_cb_func 见nim_vchat_def.h
  * @param[in] mode NIMVideoChatMode 启动音视频通话类型 见nim_vchat_def.h
  * @param[in] apns_text 自定义推送字段，填空用默认推送
  * @param[in] custom_info 自定义数据，用于透传给接收方
  * @param[in] json_extension Json string 扩展，kNIMVChatUids成员id列表(必填),其他可选 如{"uids":["uid_temp"],"custom_video":0, "custom_audio":0, "video_quality":0, "session_id":"1231sda"}
  * @param[in] user_data 无效的扩展字段
  * @return bool true 调用成功，false 调用失败可能有正在进行的通话
  */
NIM_SDK_DLL_API bool nim_vchat_start(NIMVideoChatMode mode, const char *apns_text, const char *custom_info, const char *json_extension, const void *user_data);

/** @fn bool nim_vchat_set_talking_mode(NIMVideoChatMode mode, const char *json_extension)
  * NIM VCHAT 设置通话模式，在更改通话模式后，通知底层
  * @param[in] mode NIMVideoChatMode 音视频通话类型 见nim_vchat_def.h
  * @param[in] json_extension 无效的扩展字段
  * @return bool true 调用成功，false 调用失败
  */
NIM_SDK_DLL_API bool nim_vchat_set_talking_mode(NIMVideoChatMode mode, const char *json_extension);
//回应邀请

/** @fn bool nim_vchat_callee_ack(__int64 channel_id, bool accept, const char *json_extension, const void *user_data)
  * NIM VCHAT 回应音视频通话邀请，异步回调nim_vchat_cb_func 见nim_vchat_def.h
  * @param[in] channel_id 音视频通话通道id
  * @param[in] accept true 接受，false 拒绝
  * @param[in] json_extension 扩展的json string,接起时有效 参数可选 如{"custom_video":0, "custom_audio":0, "video_quality":0, "session_id":"1231sda"}
  * @param[in] user_data 无效的扩展字段
  * @return bool true 调用成功，false 调用失败（可能channel_id无匹配，如要接起另一路通话前先结束当前通话）
  */
NIM_SDK_DLL_API bool nim_vchat_callee_ack(__int64 channel_id, bool accept, const char *json_extension, const void *user_data);

/** @fn bool nim_vchat_control(__int64 channel_id, NIMVChatControlType type, const char *json_extension, const void *user_data)
  * NIM VCHAT 音视频通话控制，异步回调nim_vchat_cb_func 见nim_vchat_def.h
  * @param[in] channel_id 音视频通话通道id
  * @param[in] type NIMVChatControlType 见nim_vchat_def.h
  * @param[in] json_extension 无效的扩展字段
  * @param[in] user_data 无效的扩展字段
  * @return bool true 调用成功，false 调用失败
  */
NIM_SDK_DLL_API bool nim_vchat_control(__int64 channel_id, NIMVChatControlType type, const char *json_extension, const void *user_data);

/** @fn void nim_vchat_set_viewer_mode(bool viewer)
  * NIM VCHAT 设置观众模式（多人模式下），全局有效（重新发起时也生效），观众模式能减少运行开销
  * @param[in] viewer 是否观众模式
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_vchat_set_viewer_mode(bool viewer);

/** @fn bool nim_vchat_get_viewer_mode()
  * NIM VCHAT 获取当前是否是观众模式
  * @return bool true 观众模式，false 非观众模式
  */
NIM_SDK_DLL_API bool nim_vchat_get_viewer_mode();

/** @fn void nim_vchat_set_audio_mute(bool muted)
  * NIM VCHAT 设置音频静音，全局有效（重新发起时也生效）
  * @param[in] muted true 静音，false 不静音
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_vchat_set_audio_mute(bool muted);

/** @fn bool nim_vchat_audio_mute_enabled()
  * NIM VCHAT 获取音频静音状态
  * @return bool true 静音，false 不静音
  */
NIM_SDK_DLL_API bool nim_vchat_audio_mute_enabled();

/** @fn void nim_vchat_set_member_in_blacklist(const char *uid, bool add, bool audio, const char *json_extension, nim_vchat_opt_cb_func cb, const void *user_data)
  * NIM VCHAT 设置单个成员的黑名单状态，当前通话有效(只能设置进入过房间的成员)
  * @param[in] uid 成员account
  * @param[in] add true表示添加到黑名单，false表示从黑名单移除
  * @param[in] audio true表示音频黑名单，false表示视频黑名单
  * @param[in] json_extension 无效扩展字段
  * @param[in] cb 结果回调见nim_vchat_def.h，返回的json_extension无效
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_vchat_set_member_in_blacklist(const char *uid, bool add, bool audio, const char *json_extension, nim_vchat_opt_cb_func cb, const void *user_data);

/** @fn void nim_vchat_start_record(const char *path, const char *json_extension, nim_vchat_mp4_record_opt_cb_func cb, const void *user_data)
  * NIM VCHAT 开始录制MP4文件，一次只允许一个录制文件，在通话开始的时候才有实际数据
  * @param[in] path 文件录制路径
  * @param[in] json_extension 无效扩展字段
  * @param[in] cb 结果回调见nim_vchat_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_vchat_start_record(const char *path, const char *json_extension, nim_vchat_mp4_record_opt_cb_func cb, const void *user_data);

/** @fn void nim_vchat_stop_record(const char *json_extension, nim_vchat_mp4_record_opt_cb_func cb, const void *user_data)
  * NIM VCHAT 停止录制MP4文件
  * @param[in] json_extension 无效扩展字段
  * @param[in] cb 结果回调见nim_vchat_def.h
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_vchat_stop_record(const char *json_extension, nim_vchat_mp4_record_opt_cb_func cb, const void *user_data);

/** @fn void nim_vchat_end(const char *json_extension)
  * NIM VCHAT 结束通话(需要主动在通话结束后调用，用于底层挂断和清理数据)
  * @param[in] json_extension 可扩展添加kNIMVChatSessionId，用于关闭对应的通话，如果kNIMVChatSessionId缺省则关闭当前通话
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_vchat_end(const char *json_extension);

/** @fn void nim_vchat_create_room(const char *room_name, const char *custom_info, const char *json_extension, nim_vchat_opt2_cb_func cb, const void *user_data)
  * NIM VCHAT 创建一个多人房间（后续需要主动调用加入接口进入房间）
  * @param[in] room_name 房间名
  * @param[in] custom_info 自定义的房间信息（加入房间的时候会返回）
  * @param[in] json_extension 无效扩展字段
  * @param[in] cb 结果回调见nim_vchat_def.h，返回的json_extension无效
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_vchat_create_room(const char *room_name, const char *custom_info, const char *json_extension, nim_vchat_opt2_cb_func cb, const void *user_data);

/** @fn bool nim_vchat_join_room(NIMVideoChatMode mode, const char *room_name, const char *json_extension, nim_vchat_opt2_cb_func cb, const void *user_data)
  * NIM VCHAT 加入一个多人房间（进入房间后成员变化等，等同点对点nim_vchat_cb_func）
  * @param[in] mode NIMVideoChatMode 音视频通话类型 见nim_vchat_def.h
  * @param[in] room_name 房间名
  * @param[in] json_extension 可选 如{"custom_video":0, "custom_audio":0, "video_quality":0, "session_id":"1231sda"}
  * @param[in] cb 结果回调见nim_vchat_def.h，返回的json_extension扩展字段中包含 kNIMVChatCustomInfo,kNIMVChatSessionId
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return bool true 调用成功，false 调用失败可能有正在进行的通话
  */
NIM_SDK_DLL_API bool nim_vchat_join_room(NIMVideoChatMode mode, const char *room_name, const char *json_extension, nim_vchat_opt2_cb_func cb, const void *user_data);

/** @fn void nim_vchat_set_video_quality(int video_quality, const char *json_extension, nim_vchat_opt_cb_func cb, const void *user_data)
  * NIM 通话中修改分辨率，只在多人中支持
  * @param[in] video_quality 分辨率模式
  * @param[in] json_extension 无效扩展字段
  * @param[in] cb 结果回调见nim_vchat_def.h，返回的json_extension无效
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_vchat_set_video_quality(int video_quality, const char *json_extension, nim_vchat_opt_cb_func cb, const void *user_data);

/** @fn void nim_vchat_set_custom_data(bool custom_audio, bool custom_video, const char *json_extension, nim_vchat_opt_cb_func cb, const void *user_data)
  * NIM 通话中修改自定义音视频数据模式
  * @param[in] custom_audio true表示使用自定义的音频数据，false表示不使用
  * @param[in] custom_video true表示使用自定义的视频数据，false表示不使用
  * @param[in] json_extension 无效扩展字段
  * @param[in] cb 结果回调见nim_vchat_def.h，返回的json_extension无效
  * @param[in] user_data APP的自定义用户数据，SDK只负责传回给回调函数cb，不做任何处理！
  * @return void 无返回值
  */
NIM_SDK_DLL_API void nim_vchat_set_custom_data(bool custom_audio, bool custom_video, const char *json_extension, nim_vchat_opt_cb_func cb, const void *user_data);

#ifdef __cplusplus
};
#endif //__cplusplus
#endif //NIM_SDK_DLL_API_NIM_VCHAT_H_