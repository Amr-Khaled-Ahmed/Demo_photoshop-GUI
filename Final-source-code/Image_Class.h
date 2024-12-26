


/**
 * @File  : Image_Class.h
 * @brief : This file contains the declaration of the Image class using Qt.
 *
 * @authors : Shehab Diab, Youssef Mohamed , Nada Ahmed.
 *                       Dr Mohamed El-Ramely ,
 * @copyright : FCAI Cairo University
 * @date      : 18/3/2024
 */

#ifndef IMAGE_CLASS_H
#define IMAGE_CLASS_H

#include <QString>
#include <QByteArray>
#include <QDebug>
#include <stdexcept>
#include "stb_image.h"
#include "stb_image_write.h"

#define ll long long
#define PNG_TYPE 1
#define BMP_TYPE 2
#define TGA_TYPE 3
#define JPG_TYPE 4
#define UNSUPPORTED_TYPE -1

/**
 * @class Image
 * @brief Represents an image with functionalities for loading, saving, and manipulating pixels.
 */
class Image {
private:
    /**
     * @brief Checks if the given filename has a valid extension.
     *
     * @param filename The filename to check.
     * @return True if the filename has a valid extension, false otherwise.
     */
    bool isValidFilename(const QString& filename) {
        if (!filename.contains('.')) {
            qWarning() << "Invalid filename: " << filename;
            return false;
        }
        return true;
    }

    /**
     * @brief Determines the image type based on the file extension.
     *
     * @param extension The file extension to determine the type.
     * @return The type of image format.
     */
    short getExtensionType(const QString& extension) {
        if (extension == ".png") {
            return PNG_TYPE;
        }
        if (extension == ".bmp") {
            return BMP_TYPE;
        }
        if (extension == ".tga") {
            return TGA_TYPE;
        }
        if (extension == ".jpg" || extension == ".jpeg") {
            return JPG_TYPE;
        }

        qWarning() << "Unsupported image format: " << extension;
        return UNSUPPORTED_TYPE;
    }

private:
    QString filename; ///< Stores the filename of the image.

public:
    int width = 0; ///< Width of the image.
    int height = 0; ///< Height of the image.
    int channels = 3; ///< Number of color channels in the image.
    QByteArray imageData; ///< QByteArray to store the image data.

    /**
     * @brief Default constructor for the Image class.
     */
    Image() = default;

    /**
     * @brief Constructor that loads an image from the specified filename.
     *
     * @param filename The filename of the image to load.
     */
    Image(QString filename) : filename(filename) {
        loadNewImage(this->filename);
    }

    /**
     * @brief Constructor that creates an image with the specified dimensions.
     *
     * @param mWidth The width of the image.
     * @param mHeight The height of the image.
     */
    Image(int mWidth, int mHeight) {
        this->width = mWidth;
        this->height = mHeight;
        this->imageData.resize(mWidth * mHeight * this->channels);
    }

    /**
     * @brief Destructor for the Image class.
     */
    ~Image() {
        if (!imageData.isEmpty()) {
            stbi_image_free(imageData.data());
        }
    }

    /**
     * @brief Loads a new image from the specified filename.
     *
     * @param filename The filename of the image to load.
     * @return True if the image is loaded successfully, false otherwise.
     * @throws std::invalid_argument If the filename or file format is invalid.
     */
    bool loadNewImage(const QString& filename) {
        if (!isValidFilename(filename)) {
            qWarning() << "Couldn't Load Image";
            throw std::invalid_argument("The file extension does not exist");
        }

        QString extension = filename.mid(filename.lastIndexOf('.'));
        short extensionType = getExtensionType(extension);
        if (extensionType == UNSUPPORTED_TYPE) {
            qWarning() << "Unsupported File Format";
            throw std::invalid_argument("File Extension is not supported, Only .JPG, .JPEG, .BMP, .PNG, .TGA are supported");
        }

        if (!imageData.isEmpty()) {
            stbi_image_free(imageData.data());
        }

        unsigned char* imgData = stbi_load(filename.toStdString().c_str(), &width, &height, &channels, STBI_rgb);
        if (imgData == nullptr) {
            qWarning() << "File Doesn't Exist";
            throw std::invalid_argument("Invalid filename, File does not exist");
        }

        imageData = QByteArray(reinterpret_cast<char*>(imgData), width * height * channels);
        return true;
    }

    /**
     * @brief Saves the image to the specified output filename.
     *
     * @param outputFilename The filename to save the image.
     * @return True if the image is saved successfully, false otherwise.
     * @throws std::invalid_argument If the output filename or file format is invalid.
     */
    bool saveImage(const QString& outputFilename) {
        if (!isValidFilename(outputFilename)) {
            qWarning() << "Not Supported Format";
            throw std::invalid_argument("The file extension does not exist");
        }

        QString extension = outputFilename.mid(outputFilename.lastIndexOf('.'));
        short extensionType = getExtensionType(extension);
        if (extensionType == UNSUPPORTED_TYPE) {
            qWarning() << "File Extension is not supported";
            throw std::invalid_argument("Only .JPG, .JPEG, .BMP, .PNG, .TGA are supported");
        }

        if (extensionType == PNG_TYPE) {
            stbi_write_png(outputFilename.toStdString().c_str(), width, height, STBI_rgb, imageData.data(), width * 3);
        } else if (extensionType == BMP_TYPE) {
            stbi_write_bmp(outputFilename.toStdString().c_str(), width, height, STBI_rgb, imageData.data());
        } else if (extensionType == TGA_TYPE) {
            stbi_write_tga(outputFilename.toStdString().c_str(), width, height, STBI_rgb, imageData.data());
        } else if (extensionType == JPG_TYPE) {
            stbi_write_jpg(outputFilename.toStdString().c_str(), width, height, STBI_rgb, imageData.data(), 90);
        }

        return true;
    }

    /**
     * @brief Gets the pixel value at the specified position and channel.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param c The color channel index (0 for red, 1 for green, 2 for blue).
     * @return Reference to the pixel value.
     * @throws std::out_of_range If the coordinates or channel index is out of bounds.
     */
    unsigned char& getPixel(int x, int y, int c) {
        if (x >= width || x < 0) {
            qWarning() << "Out of width bounds";
            throw std::out_of_range("Out of bounds, Cannot exceed width value");
        }
        if (y >= height || y < 0) {
            qWarning() << "Out of height bounds";
            throw std::out_of_range("Out of bounds, Cannot exceed height value");
        }
        if (c < 0 || c > 2) {
            qWarning() << "Out of channels bounds";
            throw std::out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        return reinterpret_cast<unsigned char&>(imageData[(y * width + x) * channels + c]);
    }

    /**
     * @brief Sets the pixel value at the specified position and channel.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param c The color channel index (0 for red, 1 for green, 2 for blue).
     * @param value The new value to set.
     * @throws std::out_of_range If the coordinates or channel index is out of bounds.
     */
    void setPixel(int x, int y, int c, unsigned char value) {
        if (x >= width || x < 0) {
            qWarning() << "Out of width bounds";
            throw std::out_of_range("Out of bounds, Cannot exceed width value");
        }
        if (y >= height || y < 0) {
            qWarning() << "Out of height bounds";
            throw std::out_of_range("Out of bounds, Cannot exceed height value");
        }
        if (c < 0 || c > 2) {
            qWarning() << "Out of channels bounds";
            throw std::out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        imageData[(y * width + x) * channels + c] = value;
    }

    /**
     * @brief Overloaded function call operator to access pixels.
     *
     * @param row The row index of the pixel.
     * @param col The column index of the pixel.
     * @param channel The color channel index (0 for red, 1 for green, 2 for blue).
     * @return Reference to the pixel value.
     */
    unsigned char& operator()(int row, int col, int channel) {
        return getPixel(row, col, channel);
    }
};

#endif // IMAGE_CLASS_H
