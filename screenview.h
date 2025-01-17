﻿#ifndef SCREENVIEW_H
#define SCREENVIEW_H
#include <QtWidgets/QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "struct.h"
#include "LinePaint.h"
#include "RectPaint.h"
#include "TextPaint.h"
#include "ColorItem.h"
#include "PointSizeWidget.h"
#include "ResultWindow.h"

typedef RectPaint EllipsePaint;


class ScreenView : public QWidget
{
	Q_OBJECT

public:
	ScreenView(QWidget *parent = NULL);	
	~ScreenView();

	void setBackGroundPixmap(QPixmap &px);

	/**
	 * @brief: 调整点的大小,保证左上小于右下
	 **/
	void setTopLeftAndButtomRight(QPointF &ptTL, QPointF &ptBR);	

	/**
	 * @brief:根据传入点构造矩形
	 **/
	QRectF getRectF(QPointF p1, QPointF p2);	

	/**
	 * @brief:获当前鼠标在矩形区域的位置
	 **/
	CursorLocation caputerCursor(QRectF rect, qreal x, qreal y);

public slots:
	void copyImage();
	void saveImage();
	void drawLine();
	void drawRect();
	void drawEllipse();
	void drawTextStatus();

	void colorItemChanged(const QColor &color);
	void colorSelection();

	void pointSizeChanged(int point_size);

	void btnBrushClicked();

    /**
     * @brief uploadPicGo 上传图片到PicGo
     */
    void uploadPicGo();

    /**
     * @brief ocrText ocr识别文字
     */
    void ocrText();

private:
	void init();

	/**
	* @brief: 初始化颜色工具条
	**/
	void initColorBar();

	void showColorBar();

	void hideColorBar();

	/**
	 * @brief: 初始化截屏大小的显示标签
	 **/
	void initLabel();

	void showLabel();

	void hideLabel();

	/**
	 * @brief: 初始化截屏工具条
	 **/
	void initToolBar();	
	
	void showToolBar();	
	
	void hideToolBar();

	/**
	 * @brief: 截取屏幕矩形区域rect部分的图像
	 **/
	void screenCapture(const QRectF &rect);

	/**
	 * @brief: 调整截取范围的大小
	 **/
	void adjustShotScreen(QMouseEvent *event);

	/**
	 * @brief: 绘制文本到截屏上
	 **/
	void drawText(QMouseEvent *event);

protected:
	void mousePressEvent(QMouseEvent *event)   Q_DECL_OVERRIDE;
	void mouseMoveEvent(QMouseEvent *event)    Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
	void keyPressEvent(QKeyEvent *event)       Q_DECL_OVERRIDE;
	void paintEvent(QPaintEvent *event)        Q_DECL_OVERRIDE;

private:
	QPixmap _fullPixmap;
	QPixmap _shotPixmap;
	double _screen_width;
	double _screen_height;
	
	QPointF _ptS;
	QPointF _ptE;
	QPointF _ptDrag;
	QRectF _shortArea;
	DrawStatus _draw_flag;
	DrawEditFlag _draw_edit_flag;
	QClipboard *_clipboard;
	CursorLocation _curlocation;    //当前鼠标位置

	QWidget *_toolbar;              //工具条
	QWidget *_colorbar;             //颜色工具条
	QPushButton *_btn_copy;
	QPushButton *_btn_save;
	QPushButton *_btn_drawLine;
	QPushButton *_btn_drawRect;
	QPushButton *_btn_drawEllipse;
	QPushButton *_btn_drawText;
	QPushButton *_btn_brush;
    QPushButton *_btn_uploadPicGo;
    QPushButton *_btn_ocr;
	QLabel *_label;

	QList<LinePaint> _line_list;
	QList<RectPaint> _rect_list;
	QList<EllipsePaint> _ellipse_list;
	QList<TextPaint*> _text_list;

	ColorItem *_cur_coloritem;
	QColor _pen_color;
	QBrush _brush;
	int _point_size;

	bool _bIsDrawLineEnd;//判断当前绘制线段是否结束
	bool _bIsBrushed;//判断当前是否填充模式

};

#endif // SCREENVIEW_H
