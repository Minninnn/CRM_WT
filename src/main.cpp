#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WServer.h>
#include <memory> // ��� std::unique_ptr � std::make_unique
#include <iostream>

// ����� ����������, ������������� �� Wt::WApplication
class HelloWorldApplication : public Wt::WApplication {
public:
    HelloWorldApplication(const Wt::WEnvironment& env) : Wt::WApplication(env) {
        // ������������� ��������� ��������
        setTitle("Hello Wt!");

        // ������ ��������� ��� ��������
        Wt::WContainerWidget* container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());

        // ������ ����� "Hello, Wt!"
        Wt::WText* helloText = container->addWidget(std::make_unique<Wt::WText>("Hello, Wt!"));

        // ��������� ������� ������
        container->addWidget(std::make_unique<Wt::WBreak>());

        // ������ ������ � �������� "Click me"
        Wt::WPushButton* button = container->addWidget(std::make_unique<Wt::WPushButton>("Click me"));

        // ������������ ������� ������� �� ������
        button->clicked().connect([=]() {
            helloText->setText("Button was clicked!");
            });
    }
};

// ������� ��� �������� ���������� ����������
std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env) {
    return std::make_unique<HelloWorldApplication>(env);
}

int main(int argc, char* argv[]) {
    try {
        // ������ ������ Wt
        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

        // ��������� ����� ����� ��� ����������
        server.addEntryPoint(Wt::EntryPointType::Application, &createApplication);

        // ��������� ������
        if (server.start()) {
            std::cout << "Application started on http://localhost:8080" << std::endl;
            std::cout << "Press Enter to stop the server..." << std::endl;
            std::cin.get(); // �������� ������� Enter

            // ������������� ������
            server.stop();
            std::cout << "Server stopped" << std::endl;
        }
        else {
            std::cerr << "Error: Failed to start server" << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1; // ���������� ��� ������
    }
    return 0;
}
