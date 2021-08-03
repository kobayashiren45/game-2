 #include "CPlayer.h"
#include "CKey.h"
#include "CBullet.h"
#define G 1
#define VJ0 18
//extern�F���̃\�[�X�t�@�C���̊O���ϐ��ɃA�N�Z�X����錾
extern CTexture Texture;
CPlayer*CPlayer::spInstance = 0;
CPlayer::CPlayer()
: mFx(1.0f), mFy(0.0f)
, FireCount(0), HP(3)
,mVj(0)
, mJump(0)

{
	mTag = EPLAYER;
	spInstance = this;
	
}

void CPlayer::Update() {

	//static���\�b�h�͂ǂ�����ł��Ăׂ�
	if (CKey::Push('A')) {
		x -= 3;
		mFx = -1;
		mFy = 0;
		if (x - w < -400) {
			x = -400 + w;
		}
	}
	if (CKey::Push('D')) {
		x += 3;
		mFx = 1;
		mFy = 0;
	
	}


	//�X�y�[�X�L�[�Œe����
	//0���傫���Ƃ�1���Z����
	if (FireCount > 0) {
		FireCount--;
	}
	//FireCont��0�ŁA���A�X�y�[�X�L�[�Œe����
	else if( CKey::Once(' ')) {
		CBullet *Bullet = new CBullet();
		//���ˈʒu�̐ݒ�
		Bullet->x = x;
		Bullet->y = y;
		//�ړ��̒l��ݒ�
		Bullet->mFx = mFx * 5;
		Bullet->mFy = mFy * 5;
		//�L���ɂ���
		Bullet->mEnabled = true;
		//�v���C���[�̒e��ݒ�
		Bullet->mTag = CRectangle::EPLAYERBULLET;
		FireCount = 10;
		
	}
	if (mJump == 0 && CKey::Push('J')) {
		//�W�����v�͂𑬓x�ɐݒ�
		mVj = VJ0;
		//�t���O��1���Z
		mJump++;
	}
	//���x�ɏd�͉����x���Z
	mVj -= G;
	//���x���ړ�
	y += mVj;


}

void CPlayer::Render() {
	CRectangle::Render(Texture, 146 - 16, 146 + 16, 146 + 16, 146 - 16);
}

void CPlayer::Collision(CRectangle *ri, CRectangle *ry) {
	if (ry->mTag == EBLOCK) {
		int mx, my;
		if (CRectangle::Collision(ry, &mx, &my)) {
			//abs(x) x�̐�Βl�����߂�
			//�ړ��ʂ����Ȃ����������ړ�������
			if (abs(mx) < abs(my)) {
				//Rect��x�����ړ�����
				x += mx;
			}

			


			else {
				//Rect��y�����ړ�����
				y += my;
				mVj = 0;	//�W�����v���x0
				if (my > 0)
				{
					//�W�����v�\
					mJump = 0;
				}

			}
	
		}
	}
	else if (CRectangle::Collision(*ry)) {
		switch (ry->mTag) {
		case EBLOCK:
			//�Փ˂��Ă���Δ��]
			mFx *= -1;
			mFy *= -1;
			break;
		case EENEMYBULLET:
			HP -= 1;
			//�v���C���[�̒e�ɓ�����ƁA�����ɂ���
			if (HP == 0){
				mEnabled = false;

			}
			break;


		}

	}
}
