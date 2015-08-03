#include "osg3d.h"
#include "custommanipulator.h"

OSG3D::OSG3D(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_pMotion = nullptr;

	init();

	addAvater();
	connect(ui.actionMotion, SIGNAL(triggered()), this, SLOT(slotMotion()));
}

OSG3D::~OSG3D()
{

}

void OSG3D::init()
{
	m_pOSGView = new GraphicsView;
	this->setCentralWidget(m_pOSGView);

	m_pManipulator = new CSManipulator;

	osg::ref_ptr<osg::MatrixTransform> matRoom = new osg::MatrixTransform;
	matRoom->addChild(osgDB::readNodeFile(
		"E:/project/3rdparty/OSG3.4.0/Data/ceep.ive"));
	//matRoom->setMatrix(osg::Matrix::translate(osg::Vec3d(0, 10000, 0)));

	m_pOSGView->getRoot()->addChild(matRoom);

	m_pManipulator->setCollisionNode(m_pOSGView->getRoot());

	//m_pOSGView->getOSGViewer()->setCameraManipulator(m_pManipulator);
}

void OSG3D::slotMotion()
{
	if (ui.actionMotion->isChecked())
	{
		if (m_pMotion == nullptr)
		{
			m_pMotion = new Motion(m_pOSGView);
			m_pMotion->show();
		}
	}
	else
	{
		delete m_pMotion;
		m_pMotion = nullptr;
	}
}

void OSG3D::addAvater()
{
	osg::Node* pAvater = osgDB::readNodeFile(
		QStringLiteral("E:/GreatMap/project/src/GM3DPlatform/Win32/Data/People/����.fbx").toLocal8Bit().data());

	osg::MatrixTransform* pMat = new osg::MatrixTransform;
	pMat->addChild(pAvater);

	// ��ת�����ţ�ƽ��
// 	osg::Matrix matrix = pMat->getMatrix();
// 	matrix.preMultRotate(osg::Quat(osg::PI_2, osg::Z_AXIS));
// 	matrix.setTrans(osg::Vec3d(0, 10000, 0));
	pMat->setMatrix(osg::Matrix::rotate(osg::Quat(osg::PI_2, osg::Z_AXIS)));

	//m_pManipulator->attachMaster(pMat);
	//m_pOSGView->getRoot()->addChild(pMat);

	CustomManipulator* pManipulator = new CustomManipulator;
	pManipulator->setCollisionNode(m_pOSGView->getRoot());
	m_pOSGView->getOSGViewer()->setCameraManipulator(pManipulator);

	// ����������
	osg::MatrixTransform* pAxes = new osg::MatrixTransform;
	pAxes->addChild(osgDB::readNodeFile("E:/project/3rdparty/OSG3.4.0/Data/axes.osgt"));
	osg::Matrix mt;
	//mt.makeScale(100, 100, 100);
	mt.setTrans(osg::Vec3d(7.925523, 5.693671, 1.700000));
	m_pOSGView->getRoot()->addChild(pAxes);
	osg::MatrixTransform* pAxes1 = new osg::MatrixTransform;
	pAxes1->addChild(osgDB::readNodeFile("E:/project/3rdparty/OSG3.4.0/Data/axes.osgt"));
	pAxes1->setMatrix(mt);
	m_pOSGView->getRoot()->addChild(pAxes1);
	m_pManipulator->attachMaster(pAxes);
	//pManipulator->setAxesNode(pAxes);
}
