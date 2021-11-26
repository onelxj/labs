#include <iostream>
#include <string>
#include <vector>

struct Part
{
    Part(std::string n, double p)
        : name(std::move(n)), price(p) {}
    std::string name;
    double price;
};

struct RAM : public Part
{
    RAM(std::string n, double p, size_t c, size_t sr, size_t sw)
        : Part(n, p), capacity(c), speed_read(sr), speed_write(sw){};
    size_t capacity;
    size_t speed_read;
    size_t speed_write;
};

struct CPU : public Part
{
    CPU(std::string n, double p, size_t f, size_t cn)
        : Part(n, p), frequency(f), cores_number(cn){};
    size_t frequency;
    size_t cores_number;
};

struct Storage : public Part
{
    Storage(std::string n, double p, size_t c, size_t sr, size_t sw)
        : Part(n, p), capacity(c), speed_read(sr), speed_write(sw){};
    size_t capacity;
    size_t speed_read;
    size_t speed_write;
};

struct Graphics : public Part
{
    Graphics(std::string n, double p, size_t s, size_t c)
        : Part(n, p), speed(s), capacity(c){};
    size_t speed;
    size_t capacity;
};

struct Computer
{
    Computer(CPU c, RAM r, Storage s, Graphics g)
        : cpu(std::move(c)), ram(std::move(r)), storage(std::move(s)),
          graphics(std::move(g))
    {
        price = cpu.price + ram.price + storage.price + graphics.price;
    }

    void info() const
    {
        std::cout << "Price: " << price << "\n";
        std::cout << "CPU name: " << cpu.name << "\n";
        std::cout << "CPU cores: " << cpu.cores_number << "\n";
        std::cout << "CPU frequency: " << cpu.frequency << "\n";
        std::cout << "RAM name: " << ram.name << "\n";
        std::cout << "RAM capacity: " << ram.capacity << "\n";
        std::cout << "RAM read speed: " << ram.speed_read << "\n";
        std::cout << "RAM write speed: " << ram.speed_write << "\n";
        std::cout << "GPU name: " << graphics.name << "\n";
        std::cout << "GPU speed: " << graphics.speed << "\n";
        std::cout << "GPU capacity: " << graphics.capacity << "\n";
        std::cout << "Storage name: " << storage.name << "\n";
        std::cout << "Storage capacity: " << storage.capacity << "\n";
        std::cout << "Storage read speed: " << storage.speed_read << "\n";
        std::cout << "Storage write speed: " << storage.speed_write << "\n\n";
    }

    RAM ram;
    CPU cpu;
    Storage storage;
    Graphics graphics;
    double price;
};

int main()
{
    std::vector<Computer> v;

    v.push_back(Computer({"Intel core i5", 1000, 2, 4}, {"Corsair", 500, 8000, 2500, 2000},
                         {"Samsung", 250, 250000, 1000, 800}, {"GTX 1050Ti", 2000, 1300, 4000}));

    v.push_back(Computer({"AMD Ryzen 2700", 1000, 4, 8}, {"Samsung", 500, 16000, 2500, 2000},
                         {"Sony", 500, 1000000, 2000, 2500}, {"GTX 1650Ti", 6000, 2000, 6000}));

    std::cout << "Whole list:\n";

    int idx = 0;
    int freq = 0;
    int found = 0;
    for (const auto &c : v)
    {
        if (c.cpu.frequency > freq)
        {
            freq = c.cpu.frequency;
            found = idx;
        }

        c.info();
        idx++;
    }

    std::cout << "\nHigher speed:\n";
    v[found].info();

    return 0;
}