#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum WINMODE { MODE_FULL, MODE_WIN };

	// Dynamic ������Ʈ ��� �� �����Ӹ��� �����ؾ��ϴ� ������Ʈ ����
	enum COMPONENTID { ID_DYNAMIC, ID_STATIC, ID_END };

	enum INFO {	INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };
	enum ROTATION { ROT_X, ROT_Y, ROT_Z, ROT_END };

	enum TEXTUREID { TEX_NORMAL, TEX_CUBE, TEX_END };

	enum RENDERID { RENDER_PRIORITY, RENDER_NONALPHA, RENDER_ALPHA, RENDER_UI, RENDER_END };

	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };
	enum MOUSEMOVESTATE {	DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };

	// �ൿ ������ �����ص� �ǳ�, ������ DIAGONAL�� ���� �ൿ ������ ���� ��
	enum PLAYERSTATE
	{
		PLY_IDLE,
		PLY_IDLEDIAGONAL,
		PLY_MOVE,
		PLY_MOVEDIAGONAL,
		PLY_DASH,
		//PLY_DASHDIAGONAL,
		PLY_END
	};

	// ���� �������� �� ��
	enum OBJ_DIRECTION
	{
		OBJDIR_FRONT = 1,
		OBJDIR_BACK = 2,
		OBJDIR_LEFT = 4,
		OBJDIR_RIGHT = 8,

		OBJDIR_LEFTFRONT = 5,
		OBJDIR_LEFTBACK = 6,
		OBJDIR_RIGHTFRONT = 9,
		OBJDIR_RIGHTBACK = 10,

		OBJDIR_NONE = 0,
		OBJDIR_END
	};
}
#endif // Engine_Enum_h__
