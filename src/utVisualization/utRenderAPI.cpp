#include "utRenderAPI.h"

#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/function.hpp>

using namespace Ubitrack;
using namespace Ubitrack::Visualization;

// the singleton render manager object
static boost::scoped_ptr< RenderManager > g_pRenderManager;
static int g_RefRenderManager = 0;



VirtualWindow::VirtualWindow(int _width, int _height, const std::string &_title)
        : m_width(_width), m_height(_height), m_title(_title) {
}

VirtualWindow::~VirtualWindow() {

}

bool VirtualWindow::is_valid() {
    return false;
}

bool VirtualWindow::create() {
    return false;
}

void VirtualWindow::destroy() {

}

void VirtualWindow::initGL(boost::shared_ptr<CameraHandle>& cam) {

}

void VirtualWindow::reshape(int w, int h) {

}

CameraHandle::CameraHandle(std::string &_name, int _width, int _height, Drivers::VirtualCamera* _handle)
        : m_sWindowName(_name)
        , m_initial_width(_width)
        , m_initial_height(_height)
        , m_bSetupNeeded(true)
        , m_pVirtualWindow()
        , m_pVirtualCamera(_handle)
{

}

CameraHandle::~CameraHandle() {
// delete m_pVirtualCamera ?
}

bool CameraHandle::need_setup() {
    return m_bSetupNeeded;
}

boost::shared_ptr<VirtualWindow> CameraHandle::get_window() {
    return m_pVirtualWindow;
}

bool CameraHandle::setup(boost::shared_ptr<VirtualWindow>& window) {
    m_pVirtualWindow = window;
    if (window->create()) {
        // do something to window..
        // extend in subclass
        return true;
    }
    return false;
}

void CameraHandle::teardown() {

    if (m_pVirtualWindow) {
        m_pVirtualWindow->destroy();
    }
}

void CameraHandle::render(int ellapsed_time) {
    // extend in subclass
}



void CameraHandle::on_window_size(int w, int h) {

}

void CameraHandle::on_window_close() {

}

void CameraHandle::on_keypress(int key, int scancode, int action, int mods) {

}


void CameraHandle::on_render(int ellapsed_time) {

}

void CameraHandle::on_cursorpos(double xpos, double ypos) {

}

void CameraHandle::post_redraw() {
    // maybe needed
}

void CameraHandle::keyboard(unsigned char key, int x, int y) {
    // extend in subclass
}



RenderManager& RenderManager::singleton()
{
    // prevent from race condition
    static boost::mutex singletonMutex;
    boost::mutex::scoped_lock l( singletonMutex );

    // create a new singleton if necessary
    if ( !g_pRenderManager )
        g_pRenderManager.reset( new RenderManager() );

    return *g_pRenderManager;
}



RenderManager::RenderManager()
        : m_iCameraCount(0) {
}

RenderManager::~RenderManager() {

}


void RenderManager::setup() {
    // anything to do here ... most setup should be done in the client
}

bool RenderManager::need_setup() {
    return (m_mCamerasNeedSetup.size() > 0);
}


bool RenderManager::any_windows_valid() {
    boost::mutex::scoped_lock lock( m_mutex );
    bool awv = false;
    for (CameraHandleMap::iterator it=m_mRegisteredCameras.begin(); it != m_mRegisteredCameras.end(); ++it) {
        awv |= it->second->get_window()->is_valid();
    }
    return awv;
}

boost::shared_ptr<CameraHandle> RenderManager::setup_pop_front() {
    boost::mutex::scoped_lock lock( m_mutex );
    boost::shared_ptr<CameraHandle> cam;
    if (m_mCamerasNeedSetup.size() > 0) {
        cam = m_mCamerasNeedSetup.front();
        m_mCamerasNeedSetup.pop_front();
    }
    return cam;
}

void RenderManager::setup_push_back(boost::shared_ptr<CameraHandle>& handle) {
    boost::mutex::scoped_lock lock( m_mutex );
    m_mCamerasNeedSetup.push_back(handle);
}

void RenderManager::teardown() {
    for (CameraHandleMap::iterator it=m_mRegisteredCameras.begin(); it != m_mRegisteredCameras.end(); ++it) {
        it->second->teardown();
    }
}

CameraHandleMap::iterator RenderManager::cameras_begin() {
    return m_mRegisteredCameras.begin();
}

CameraHandleMap::iterator RenderManager::cameras_end() {
    return m_mRegisteredCameras.end();
}

void RenderManager::notify_ready() {
    boost::mutex::scoped_lock lock( g_globalMutex );
    g_continue.notify_all();

    if (m_notification_slot) {
        m_notification_slot( );
    }

}

bool RenderManager::wait_for_event(int wait_time) {
    boost::mutex::scoped_lock lock( g_globalMutex );
    return g_continue.timed_wait( lock, boost::posix_time::milliseconds(wait_time) );
}

void RenderManager::register_notify_callback(CallbackType cb) {
    m_notification_slot = cb;
}

void RenderManager::unregister_notify_callback() {
    m_notification_slot = NULL;
}


unsigned int RenderManager::register_camera(boost::shared_ptr<CameraHandle>& handle) {
    boost::mutex::scoped_lock lock( m_mutex );
    unsigned int new_id = m_iCameraCount++;
    m_mRegisteredCameras[new_id] = handle;
    m_mCamerasNeedSetup.push_back(handle);
    return new_id;
}

void RenderManager::unregister_camera(unsigned int cam_id) {
    boost::mutex::scoped_lock lock( m_mutex );
    if (m_mRegisteredCameras.find(cam_id) != m_mRegisteredCameras.end()) {
        m_mRegisteredCameras.erase(cam_id);
    }
    m_iCameraCount--;
}

unsigned int RenderManager::camera_count() {
    return m_iCameraCount;
}

boost::shared_ptr<CameraHandle> RenderManager::get_camera(unsigned int cam_id) {
    boost::mutex::scoped_lock lock( m_mutex );
    boost::shared_ptr<CameraHandle> cam;
    if (m_mRegisteredCameras.find(cam_id) != m_mRegisteredCameras.end()) {
        cam = m_mRegisteredCameras[cam_id];
    }
    return cam;
}
