#pragma once

/** @defgroup EXAMPLES ���������
*  @author  �Է�
*  @version 1.0
*  @date    2006-11-9
*  @{
*/

/** @name ƽ̨�궨��
*  @{
*/
/** ��������ַ������� */
#define MAX_LOADSTRING	100
/** FPS���� */
#define FPS				60
/** @}*/ // ƽ̨�궨��
class CPlatForm
{
	/** @name ƽ̨����
	*  @{
	*/

	/** ��ʼ����AVI����״̬ */
	bool avi_end = false;
	/** ���㵱ǰAVI����ʱ��ı��� */
	int play_temp_time = 0;
	/** AVI��Ƶ���ž�� */
	static HWND avi_hw;
	/** AVI��Ƶ�ܳ��� �� */
	static long PlayTime;
	/** ���ڱ��� */
	WCHAR				szTitle[MAX_LOADSTRING];
	/** ���ڸ����� */
	WCHAR				szWindowClass[MAX_LOADSTRING];
	/** ƽ̨�൥������ */
	static CPlatForm	*Instance;
	/** ���ھ�� */
	HWND				hWnd;
	/** 3D�豸 */
	LPDIRECT3D9			pD3d;
	/** 3D��ʾ�豸 */
	LPDIRECT3DDEVICE9	pd3dDevice;
	/** �������ƶ��� */
	LPD3DXLINE			g_pLine;
	/** ���ֻ��ƶ��� */
	LPD3DXFONT			pFont;
	/** ���ֻ��ƶ��� */
	LPD3DXFONT			pFont_big;
	/** FPS��ʾ���� */
	bool				DisplayFPS = true;
	/** ��Ϸ��ͣ���� */
	bool				game_Pause;
	/** ��굱ǰx���� */
	static float		mouse_x;
	/** ��굱ǰy���� */
	static float		mouse_y;
	/** ������״̬ */
	static bool			lbutton_press;
	/** ��ʼ��3D����
	*/
	void				initD3D();
	/** ��Ϣ����
	*/
	static				LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	/** FPS��ʾ
	*/
	void				displayFPS();
	/** ͼ�����
	*/
	void				Render();
	/** ��ȡ��ǰFPSֵ
	*/
	float				getFPS();
	
public:
	/** ��Ϸ��������
	*/
	void run();
	/** ������Ϸ��ͣ����
	*  @param file pause = true ��ͣ pause = false ����
	*/
	void set_pause(bool _pause) { game_Pause = _pause; }
	/** ��ȡ��Ϸ��ͣ����״̬
	*  @return ������Ϸ��ǰ״̬
	*/
	bool get_pause() { return game_Pause; }
	/** ��ȡ���ھ��
	*  @return ���ش��ھ��
	*/
	HWND Get_hwnd() { return hWnd; }
	/** ƽ̨�൥������
	*  @return ���ص�������
	*/
	static CPlatForm *Getinstance();
	/** ��ȡ3D�豸
	*  @return ����3D�豸����
	*/
	LPDIRECT3D9 Get_pD3d() { return pD3d; }
	/** ��ȡ3D��ʾ�豸
	*  @return ����3D��ʾ�豸
	*/
	LPDIRECT3DDEVICE9	Get_pd3dDevice() { return pd3dDevice; }
	/** ��ȡ�������
	*  @return ���X����
	*/
	float get_mouse_x() { return mouse_x; }
	/** ��ȡ�������
	*  @return �������Y����
	*/
	float get_mouse_y() { return mouse_y; }
	/** ��ȡ������״̬
	*  @return ����������״̬
	*  - true	����������
	*  - false	����������

	*/
	bool get_lbutton_press() { return lbutton_press; }
	/** ��ȡ��ʱ��
	*  @return ����ÿһ���ʱ��ֵ
	*/
	float updateTime();
	/** ��ȡ���ֶ���
	*  @return �������ֶ���
	*/
	LPD3DXFONT get_p_font() { return pFont; }
	/** ��ȡ���ֶ���
	*  @return �������ֶ���
	*/
	LPD3DXFONT get_p_font_big() { return pFont_big; }
	/** �๹�캯��
	*/
	CPlatForm();
	/** ����������
	*/
	~CPlatForm();

	/** @}*/ // ƽ̨����
	/** @}*/ // ���������
};

