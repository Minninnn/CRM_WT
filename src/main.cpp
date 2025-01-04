#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WServer.h>
#include <memory> // Для std::unique_ptr и std::make_unique
#include <iostream>

// Класс приложения, наследующийся от Wt::WApplication
class HelloWorldApplication : public Wt::WApplication {
public:
    HelloWorldApplication(const Wt::WEnvironment& env) : Wt::WApplication(env) {
        // Устанавливаем заголовок страницы
        setTitle("Hello Wt!");

        // Создаём контейнер для виджетов
        Wt::WContainerWidget* container = root()->addWidget(std::make_unique<Wt::WContainerWidget>());

        // Создаём текст "Hello, Wt!"
        Wt::WText* helloText = container->addWidget(std::make_unique<Wt::WText>("Hello, Wt!"));

        // Добавляем перенос строки
        container->addWidget(std::make_unique<Wt::WBreak>());

        // Создаём кнопку с надписью "Click me"
        Wt::WPushButton* button = container->addWidget(std::make_unique<Wt::WPushButton>("Click me"));

        // Обрабатываем событие нажатия на кнопку
        button->clicked().connect([=]() {
            helloText->setText("Button was clicked!");
            });
    }
};

// Функция для создания экземпляра приложения
std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment& env) {
    return std::make_unique<HelloWorldApplication>(env);
}

int main(int argc, char* argv[]) {
    try {
        // Создаём сервер Wt
        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

        // Добавляем точку входа для приложения
        server.addEntryPoint(Wt::EntryPointType::Application, &createApplication);

        // Запускаем сервер
        if (server.start()) {
            std::cout << "Application started on http://localhost:8080" << std::endl;
            std::cout << "Press Enter to stop the server..." << std::endl;
            std::cin.get(); // Ожидание нажатия Enter

            // Останавливаем сервер
            server.stop();
            std::cout << "Server stopped" << std::endl;
        }
        else {
            std::cerr << "Error: Failed to start server" << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1; // Возвращаем код ошибки
    }
    return 0;
}
