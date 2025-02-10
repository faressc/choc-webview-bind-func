#include "modules/choc/gui/choc_WebView.h"
#include "modules/choc/gui/choc_DesktopWindow.h"
#include "modules/choc/gui/choc_MessageLoop.h"
#include <iostream>

int i = 0;

int main()
{
    choc::ui::setWindowsDPIAwareness(); // For Windows, we need to tell the OS we're high-DPI-aware

    choc::ui::DesktopWindow window ({ 100, 100, 600, 600 });

    window.setWindowTitle ("Hello");
    window.setResizable (true);
    window.setMinimumSize (300, 300);
    window.setMaximumSize (600, 600);
    window.windowClosed = [] { choc::messageloop::stop(); };

    choc::ui::WebView webview;

    assert(webview.loadedOK());

    window.setContent (webview.getViewHandle());

    assert(webview.bind ("sliderValueUpdate", [] (const choc::value::ValueView& args) -> choc::value::Value
    {
        auto message =  choc::json::toString (args);

        // This just shows how to invoke an async callback
        choc::messageloop::postMessage ([message]
        {
            std::cout << "Binded function called with message: " << message << std::endl;
        });

        std::string return_message = ("{\"message\":\"User set value (echoed back)\"}");
        return choc::value::createString (return_message);
    }));

    // webview.navigate("file:///home/leto/ak/choc_webview_test/test.html");
    webview.navigate("file:///home/faressc/tu-studio/choc_webview_test/index.html");

    window.toFront();
    choc::messageloop::run();
    return 0;
}