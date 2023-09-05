#pragma once

class UniformLocation {
public:
    explicit UniformLocation(int id)
        : id{id} {}

    void set(float v0, float v1, float v2, float v3);
private:
    int id;
};
