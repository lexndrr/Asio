#include <iostream>
#include <boost/asio.hpp>

#include <chrono>


using boost::asio::ip::tcp;

int main()
{
    try
    {
        boost::asio::io_service io_service; // input-output management

        // Создание объекта acceptor
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1234));

        // Бесконечный цикл для прослушивания входящих соединений
        while (true)
        {
            // Создание нового сокета для каждого входящего соединения
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            // Чтение сообщений от клиента и вывод их на экран
            boost::asio::streambuf receive_buffer;
            boost::system::error_code error;
            while (boost::asio::read_until(socket, receive_buffer, "\n", error))
            {
                std::string message = boost::asio::buffer_cast<const char*>(receive_buffer.data());
                if (message == "/ping")
                {

                }
                std::cout << "Message from client: " << message << std::endl;

                // Отправка ответа клиенту
                std::string response = "Server received your message!";
                boost::asio::write(socket, boost::asio::buffer(response));
                receive_buffer.consume(receive_buffer.size()); // очищаем буфер
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
