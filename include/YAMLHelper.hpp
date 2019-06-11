/**
 *  MIT License
 *
 *  Copyright (c) 2019 Yuya Kudo
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

#ifndef INCLUDE_YAMLHELPER_HPP_
#define INCLUDE_YAMLHELPER_HPP_

#include <opencv2/core.hpp>
#include <iostream>
#include <string>

namespace cvlib {
    class YAMLHelper {
    public:
        /**
         *  Read target data from YAML file
         *
         *  @filepath: path of YAML file
         *  @labels:   label name of target
         *             (if yaml file have a hierarchical structure, you should set multiple)
         *  @Return:   read data
         */
        template<typename T, class... A>
        static T read(const std::string& filepath, const A&... labels) {
            cv::FileStorage fs(filepath, cv::FileStorage::Mode::READ);
            if(!fs.isOpened()) {
                throw std::runtime_error("[" + std::string(__PRETTY_FUNCTION__) + "] " +
                                         "Can not open file : " + filepath);
            }

            T data;
            cv::FileNode node;
            auto label_list = std::initializer_list<std::string>{labels...};
            auto cnt        = label_list.size();
            if(cnt != 0) {
                for(const auto& label : label_list) {
                    if(cnt == label_list.size()) {
                        node = fs[label];
                    }
                    else {
                        node = node[label];
                    }

                    cnt--;
                    if(cnt == 0) {
                        node >> data;
                    }
                }
            }

            if(node.empty()) {
                throw std::runtime_error("[" + std::string(__PRETTY_FUNCTION__) + "] " +
                                         "Labels assingment are invalid");
            }

            return data;
        }

        /**
         *  Interface class for reading data as struct from YAML files
         *  e.g.
         *  --------------------------------------------------------
         *  %YAML:1.2
         *  ---
         *  piyo:
         *     huga:
         *        A: 10
         *        B: "test"
         *  --------------------------------------------------------
         *  class Hoge : public cvlib::YAMLHelper::Param {
         *  public:
         *      uint32_t    A;
         *      std::string B;
         *      void read(const cv::FileNode& node) override {
         *          A = (int)node["A"];
         *          B = (std::string)node["B"];
         *      }
         *  };
         *
         *  int main() {
         *      Hoge hoge;
         *      cvlib::YAMLHelper::readStruct(hoge, "./test.yaml", "piyo", "huga");
         *      std::cout << "hoge.A : " << hoge.A << std::endl;  // 10
         *      std::cout << "hoge.B : " << hoge.B << std::endl;  // test
         *  }
         *  --------------------------------------------------------
         */
        class Param {
        public:
            virtual void read(const cv::FileNode& node) = 0;
        };

        /**
         *  Read target data as struct from YAML file
         *
         *  @filepath: path of YAML file
         *  @labels:   label name of target
         *             (if yaml file have a hierarchical structure, you should set multiple)
         *  @Return:   void
         */
        template<class... A>
        static void readStruct(Param& data, const std::string& filepath, const A&... labels) {
            cv::FileStorage fs(filepath, cv::FileStorage::Mode::READ);
            if(!fs.isOpened()) {
                throw std::runtime_error("[" + std::string(__PRETTY_FUNCTION__) + "] " +
                                         "Can not open file: " + filepath);
            }

            cv::FileNode node;
            auto label_list = std::initializer_list<std::string>{labels...};
            auto cnt        = label_list.size();
            if(cnt != 0) {
                for(const auto& label : label_list) {
                    if(cnt == label_list.size()) {
                        node = fs[label];
                    }
                    else {
                        node = node[label];
                   }

                    cnt--;
                    if(cnt == 0) {
                        data.read(node);
                    }
                }
            }

            if(node.empty()) {
                throw std::runtime_error("[" + std::string(__PRETTY_FUNCTION__) + "] " +
                                         "Labels assingment are invalid");
            }
        }
    };
}

#endif /* INCLUDE_YAMLHELPER_HPP_ */
