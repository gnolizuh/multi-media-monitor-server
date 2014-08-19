#include "UsersInfoScene.h"

UsersInfoParameter::UsersInfoParameter(const pj_uint8_t *storage, pj_uint16_t storage_len)
	: UdpParameter(storage, storage_len)
{
	pj_ntoh_assign(storage, storage_len, user_count_);
	users_.resize(user_count_);

	for(pj_uint8_t idx = 0; idx < user_count_; ++ idx)
	{
		pj_ntoh_assign(storage, storage_len, users_[idx].user_id);
		pj_ntoh_assign(storage, storage_len, users_[idx].audio_ssrc);
		pj_ntoh_assign(storage, storage_len, users_[idx].video_ssrc);
	}
}

scene_opt_t UsersInfoScene::Maintain(UdpParameter *parameter, Room *room, pj_buffer_t &buffer)
{
	UsersInfoParameter *param = reinterpret_cast<UsersInfoParameter *>(parameter);
	for( pj_uint8_t idx = 0; idx < param->user_count_; ++ idx )
	{
		room->OnAddUser(param->users_[idx].user_id,
			param->users_[idx].audio_ssrc,
			param->users_[idx].video_ssrc);
	}

	return SCENE_OPT_NONE;
}
