////==========================================
//Matrix4�^�̃e�X�g
//==========================================
#include"Vector3.h"
#include"Matrix4.h"
#include<DxLib.h>
#include<cstring>
#include <cmath>
//memcpy//��(Sphere)�̕`��
//DxLib=>intDrawSphere3D(VECTORCenterPos,floatr,intDivNum,unsignedintDifColor,unsignedintSpcColor,intFillFlag);
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//�~��(Cone)�̕`��
//DxLib=>intDrawCone3D(VECTORTopPos,VECTORBottomPos,floatr,intDivNum,unsignedintDifColor,unsignedintSpcColor,intFillFlag);
int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r, const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//�����̕`��
//DxLib=>intDrawLine3D(VECTORPos1,VECTORPos2,unsignedintColor);
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

//�J�����̈ʒu�Ǝp���̐ݒ�
//DxLib=>intSetCameraPositionAndTargetAndUpVec(VECTORPosition,VECTORTarget,VECTORUp);
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//�J�����̈ʒu
	const Vector3& cameraTarget,	//�J�����̒����_
	const Vector3& cameraUp			//�J�����̏�̌���
);

//���f���̍��W�ϊ��p�s����Z�b�g����
//DxLib=>intMV1SetMatrix(intMHandle,MATRIXMatrix);
int MV1SetMatrix(const int MHandle, const Matrix4 Matrix);
//�֐��v���g�^�C�v�錾
void DrawAxis3D(const float length);	//x,y,z���̕`��
void DrawKeyOperation();				//�L�[����̕`��

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//DxLib������
	const int WindowWidth = 1024;
	const int WindowHeight = 576;

	ChangeWindowMode(TRUE);							//�E�C���h�E���[�h�ɂ���
	SetGraphMode(WindowWidth, WindowHeight, 32);	//��ʃ��[�h�̃Z�b�g
	SetBackgroundColor(0, 0, 64);					//�w�i�FRGB 
	if (DxLib_Init() == -1)return-1;				//DxLib ����������
	SetDrawScreen(DX_SCREEN_BACK);					//�`����ʂ𗠉�ʂɃZ�b�g

	SetUseZBuffer3D(TRUE);							//�y�o�b�t�@��L���ɂ���
	SetWriteZBuffer3D(TRUE);						//�y�o�b�t�@�ւ̏������݂�L���ɂ���

	//�J����������
	Vector3 cameraPosition(50.0f, 50.0f, -400.0f);
	Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3 cameraUp(0.0f, 1.0f, 0.0f);

	//�N���b�v��		��		��
	SetCameraNearFar(1.0f, 1000.0f);//�J�����̗L���͈͂�ݒ�
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f);//��ʂ̒��S���J�����̒��S�ɍ��킹��
	SetCameraPositionAndTargetAndUpVec(
		Vector3(0.0f, 0.0f, -120.0f),//�J�����̈ʒu
		//Vector3(-20.0f,20.0f,-120.0f),//�J�����̈ʒu
		Vector3(0.0f, 0.0f, 0.0f),//�J�����̒����_
		Vector3(0.0f, 1.0f, 0.0f));//�J�����̏�̌���

	//Circle
	float circleX = 10;
	float circleY = 10;
	float circleR = 30;

	//Line
	float lineX1 = 100;
	float lineY1 = 300;
	float lineX2 = 500;
	float lineY2 = 100;
	
	//Line length
	float distX = lineX1 - lineX2;
	float distY = lineY1 - lineY2;
	float len = sqrt((distX * distX) + (distY * distY));
	
	//Dot product of the line and circle
	float dot = (((circleX - lineX1) * (lineX2 - lineX1)) + ((circleY - lineY1) * (lineY2 - lineY1))) / pow(len, 2);

	float closestX = lineX1 + (dot * (lineX2 - lineX1));
	float closestY = lineX1 + (dot * (lineY2 - lineY1));
	//�Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�X�V---------------------------
		if (CheckHitKey(KEY_INPUT_S))circleY += 1;
		if (CheckHitKey(KEY_INPUT_D))circleX += 1;
		if (CheckHitKey(KEY_INPUT_W))circleY -= 1;
		if (CheckHitKey(KEY_INPUT_A))circleX -= 1;

		distX = closestX - circleX;
		distY = closestY - circleY;
		float distance = sqrt((distX * distX) + (distY * distY));
		
		//�`��---------------------------
		ClearDrawScreen();
		//��ʂ�����
		//xyz���̕`��
		DrawAxis3D(500.0f);

		//���f���̕`��
		if (distance >= circleR) {
		DrawCircle(circleX, circleY, circleR , GetColor(255, 255, 0), true);
		DrawLine(lineX1, lineY1 - 200, lineX2, lineY2 - 200, GetColor(255, 255, 0), true);
		}
		else if (distance <= circleR) {
		DrawCircle(circleX, circleY, circleR, GetColor(255, 0, 0), true);
		DrawLine(lineX1, lineY1-200, lineX2, lineY2-200, GetColor(255, 0, 0), true);
		}
		
		//DrawKeyOperation();	//�L�[����̕`��
		//�t���b�v����
		ScreenFlip();
	}

	DxLib::DxLib_End();

	//DxLib�I������
	return 0;
	//�\�t�g�̏I��
}
//xyz���̕`��
void DrawAxis3D(const float length)
{
	//���̐��̕`��
	DrawLine3D(Vector3(-length, 0, 0), Vector3(+length, 0, 0), GetColor(255, 0, 0));	//x��
	DrawLine3D(Vector3(0, -length, 0), Vector3(0, +length, 0), GetColor(0, 255, 0));	//y��
	DrawLine3D(Vector3(0, 0, -length), Vector3(0, 0, +length), GetColor(0, 0, 255));	//z��

	////���̐�̕`�� xyz���̐���ۂɁA�~��������
	//const float coneSize = 10.0f;
	//DrawCone3D(Vector3(length, 0, 0), Vector3(length - coneSize, 0, 0), coneSize / 2, 16,
	//	GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
	//DrawCone3D(Vector3(0, length, 0), Vector3(0, length - coneSize, 0), coneSize / 2, 16,
	//	GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
	//DrawCone3D(Vector3(0, 0, length), Vector3(0, 0, length - coneSize), coneSize / 2, 16,
	//	GetColor(0, 0, 255), GetColor(255, 255, 255), TRUE);
}
//�L�[����̕`��
void DrawKeyOperation()
{
	const unsigned white = GetColor(255, 255, 255);
	DrawFormatString(10, 20 * 1, white, "[W][E][R]R:���Z�b�g");
	DrawFormatString(10, 20 * 2, white, "[A][S][D]AD:y���܂��̉�]");
	DrawFormatString(10, 20 * 3, white, "[Z]WS:x���܂��̉�]");
	DrawFormatString(10, 20 * 4, white, "EZ:z���܂��̉�]");

}

//�ȍ~�ADxLib�̊e�֐���Vector3�^Matrix4�^�𗘗p�ł���悤�ɂ���֐��Q//���̕`��//DxLib=>intDrawSphere3D(VECTORCenterPos,floatr,intDivNum,unsignedintDifColor,unsignedintSpcColor,intFillFlag);
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };	//�\���̏������q���X�g

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);
}

//DxLib=>intDrawCone3D(VECTORTopPos,VECTORBottomPos,floatr,intDivNum,unsignedintDifColor,unsignedintSpcColor,intFillFlag);
int DrawCone3D(const Vector3& TopPos, const Vector3& BottomPos, const float r, const int DivNum, const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR topPos = { TopPos.x,TopPos.y,TopPos.z };
	VECTOR bottomPos = { BottomPos.x,BottomPos.y,BottomPos.z };
	return DrawCone3D(topPos, bottomPos, r, DivNum, DifColor, SpcColor, FillFlag);
}
//�����̕`��//DxLib=>intDrawLine3D(VECTORPos1,VECTORPos2,unsignedintColor);
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color)
{
	VECTOR p1 = { Pos1.x,Pos1.y,Pos1.z };//�\���̏������q���X�g
	VECTOR p2 = { Pos2.x,Pos2.y,Pos2.z };//�\���̏������q���X�g
	return DrawLine3D(p1, p2, Color);
}
//�J�����̈ʒu�Ǝp���̐ݒ�//DxLib=>intSetCameraPositionAndTargetAndUpVec(VECTORPosition,VECTORTarget,VECTORUp);
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,//�J�����̈ʒu
	const Vector3& cameraTarget,//�J�����̒����_
	const Vector3& cameraUp//�J�����̏�̌���
)
{
	VECTOR position = { cameraPosition.x,cameraPosition.y,cameraPosition.z };
	VECTOR target = { cameraTarget.x,cameraTarget.y,cameraTarget.z };
	VECTOR up = { cameraUp.x,cameraUp.y,cameraUp.z };
	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}
//���f���̍��W�ϊ��p�s����Z�b�g����
//DxLib=>intMV1SetMatrix(intMHandle,MATRIXMatrix);
int MV1SetMatrix(const int MHandle, const Matrix4 Matrix)
{
	MATRIX matrix; std::memcpy(&matrix, &Matrix, sizeof MATRIX);	//�������ԃR�s�[
	return MV1SetMatrix(MHandle, matrix);
}

