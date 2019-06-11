#include <YAMLHelper.hpp>

const std::string YAML_FILE_PATH = "../data/sample.yaml";

class MyPoint2d : public cvlib::YAMLHelper::Param {
public:
    double x;
    double y;
    void read(const cv::FileNode& node) override {
        x = (double)node["x"];
        y = (double)node["y"];
    }
};

template<typename T>
class TypeParams : public cvlib::YAMLHelper::Param {
public:
    T A;
    T B;
    T C;
    void read(const cv::FileNode& node) override {
        A = (T)node["A"];
        B = (T)node["B"];
        C = (T)node["C"];
    }
};

int main(int argc,char *argv[]) {
    try {
        auto hello = cvlib::YAMLHelper::read<std::string>(YAML_FILE_PATH, "Hello");
        std::cout << "hello : " << hello << std::endl;

        auto A = cvlib::YAMLHelper::read<std::string>(YAML_FILE_PATH, "A", "nest");
        std::cout << "A : " << A << std::endl;

        auto B = cvlib::YAMLHelper::read<std::string>(YAML_FILE_PATH, "A", "B", "nest");
        std::cout << "B : " << B << std::endl;

        auto C = cvlib::YAMLHelper::read<std::string>(YAML_FILE_PATH, "A", "B", "C", "nest");
        std::cout << "C : " << C << std::endl;

        auto D = cvlib::YAMLHelper::read<std::string>(YAML_FILE_PATH, "A", "B", "C", "D", "nest");
        std::cout << "D : " << D << std::endl;

        auto E = cvlib::YAMLHelper::read<std::string>(YAML_FILE_PATH, "A", "B", "C", "D", "E", "nest");
        std::cout << "E : " << E << std::endl;

        auto mat = cvlib::YAMLHelper::read<cv::Mat>(YAML_FILE_PATH, "cvMat");
        std::cout << "mat : " << std::endl << mat << std::endl;

        std::vector<MyPoint2d> pts;
        auto pt_num = cvlib::YAMLHelper::read<int>(YAML_FILE_PATH, "Points", "num");
        for(int i = 0; i < pt_num; i++) {
            MyPoint2d pt;
            cvlib::YAMLHelper::readStruct(pt, YAML_FILE_PATH, "Points", "Point" + std::to_string(i));
            pts.push_back(pt);
        }

        for(const auto& pt : pts) {
            std::cout << "pt : " << pt.x << ", " << pt.y << std::endl;
        }

        TypeParams<int> int_params;
        cvlib::YAMLHelper::readStruct(int_params, YAML_FILE_PATH, "IntParams");
        std::cout << "int_params.A : " << int_params.A << std::endl;
        std::cout << "int_params.B : " << int_params.B << std::endl;
        std::cout << "int_params.C : " << int_params.C << std::endl;

        TypeParams<double> double_params;
        cvlib::YAMLHelper::readStruct(double_params, YAML_FILE_PATH, "DoubleParams");
        std::cout << "double_params.A : " << double_params.A << std::endl;
        std::cout << "double_params.B : " << double_params.B << std::endl;
        std::cout << "double_params.C : " << double_params.C << std::endl;

        TypeParams<std::string> str_params;
        cvlib::YAMLHelper::readStruct(str_params, YAML_FILE_PATH, "StrParams");
        std::cout << "str_params.A : " << str_params.A << std::endl;
        std::cout << "str_params.B : " << str_params.B << std::endl;
        std::cout << "str_params.C : " << str_params.C << std::endl;
    }
    catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }
}
