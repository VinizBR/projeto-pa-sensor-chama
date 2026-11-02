#include "SensorChama.h"

#include <linux/gpio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include <cstring>
#include <stdexcept>

SensorChama::SensorChama() : fdLinha(-1) {

    int fdChip = open("/dev/gpiochip4", O_RDONLY);

    if (fdChip < 0) {
        throw std::runtime_error("Erro ao abrir GPIOE");
    }

    gpio_v2_line_request requisicao{};

    requisicao.offsets[0] = 1;
    requisicao.num_lines = 1;
    requisicao.config.flags = GPIO_V2_LINE_FLAG_INPUT;

    std::strncpy(
        requisicao.consumer,
        "sensor_chama",
        sizeof(requisicao.consumer) - 1
    );

    if (ioctl(fdChip, GPIO_V2_GET_LINE_IOCTL, &requisicao) < 0) {
        close(fdChip);
        throw std::runtime_error("Erro ao configurar PE1");
    }

    fdLinha = requisicao.fd;

    close(fdChip);
}

SensorChama::~SensorChama() {
    if (fdLinha >= 0) {
        close(fdLinha);
    }
}

bool SensorChama::lerNivel(int& nivel) const {

    gpio_v2_line_values valores{};

    valores.mask = 1;

    if (ioctl(fdLinha, GPIO_V2_LINE_GET_VALUES_IOCTL, &valores) < 0) {
        return false;
    }

    nivel = (valores.bits & 1) ? 1 : 0;

    return true;
}
