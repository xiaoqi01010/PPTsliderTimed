#include "timedslider.h"
#include "ui_timedslider.h"
/*QStringList is a doubly linked list which has overloaded operator functions which makes it easier to use.For instance:
  QStringList& operator+(const QStringList & other) const 
  QStringList& operator<<(const QString& str)

  While both QStringList and QVector are containers, QStringList is more liked a linked list while QVector is a dynamic array. 
 */
timedslider::timedslider(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::timedslider)
{
	ui->setupUi(this);
	m_index =0;
	isStarted = false;
	//This is to plant a seed for qrand() depending on the current time because return value of QTime::currenTime().msec() is always changing according to current time.  
	/*QTime::currentTime() cannot be used directly since it returns a QTime value but
	  QTime::msec() returns an unsigned integer*/
	qsrand(QTime::currentTime().msec());
	loadImages("../picturesliders/image");
	qDebug()<<"Number of pictures: "<<vecImages.size();
}

timedslider::~timedslider()
{
	delete ui;
}

void timedslider::loadImages(const QString &path){
	//Object of type path
	QDir dir(path);
	//to retrieve files
	//QStringList list1 = dir.entryList(QDir::Files);
	//But the issue is that a txt file may be retrieved.It is possible to use entryInfoList so you can QString suffix of the return value to see if the file is a picture or no.  
	QStringList list1;
	QFileInfoList fileInfoList = dir.entryInfoList(QDir::Files);
	for(int i = 0; i<fileInfoList.size();i++){
		if(fileInfoList.at(i).suffix()=="jpg" ||
				fileInfoList.at(i).suffix() == "jpeg"||
				fileInfoList.at(i).suffix() == "png"
		  ){
			list1.append(fileInfoList.at(i).fileName());
		}
	}

	for(int i = 0; i<list1.size();i++){
		//loads picture from the catenated path
		QImage image(path + "/" + list1.at(i));
		vecImages<<image;
	}
	//Recursion to call the same function with the parameter QDir::Dirs but have to only pick out the child directories
	/*Therefore QDir::NoDotAndDotDot also needs to be used*/
	QStringList list2 = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	for(int i = 0; i<list2.size();i++){
        if(list2.size()==0)break;
		loadImages(path+"/"+list2.at(i));
		
	}
	
}

void timedslider::paintEvent(QPaintEvent *){
	QPainter painter(this);
	QRect rect = ui->frame->frameRect();
	rect.translate(ui->frame->pos());
	painter.drawImage(rect,vecImages[m_index]);
}

//Button
void timedslider::on_btnStart_clicked(){
	if(isStarted == false){
		isStarted = true;
		ui->btnStart->setText("Stop");
		//collect the ID of timer 
		m_timerID = startTimer(500);
	}
	else{
		isStarted = false;
		ui->btnStart->setText("Start");
		//Stops the timer 
		killTimer(m_timerID);
	}
}

void timedslider::timerEvent(QTimerEvent* ){
	//To obtain a number that is <= the number of images. 
    m_index = qrand()%(vecImages.size());
	//Triggers the repaint event and repaints the frames
	update();
}
