# SPDX-FileCopyrightText: 2021-2025 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: CC0-1.0
import pytest
from pytest_embedded import Dut
from pytest_embedded_idf.utils import idf_parametrize


@pytest.mark.twai_transceiver
@idf_parametrize('target', ['esp32'], indirect=['target'])
def test_twai_alert_recovery_example(dut: Dut) -> None:
    dut.expect_exact('TWAI Alert and Recovery: Driver installed')
    dut.expect_exact('TWAI Alert and Recovery: Driver uninstalled')
