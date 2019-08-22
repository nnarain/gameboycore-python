from unittest import TestCase

from gameboycore import GameboyCore


class TestEmulation(TestCase):
    def setUp(self):
        self.core = GameboyCore()
        self.core.open('roms/cpu_instrs.gb')
        self.vblank_fired = False
        self.scanline_count = 0

    def test_emulate_frame(self):
        """
        Test emulating a single frame
        """
        self.core.emulate_frame()

    def test_scanline_callback(self):
        """
        Test that the scanline callback returns the correct number of lines
        """
        def cb(scanline, line_num):
            self.scanline_count += 1
        self.core.register_scanline_callback(cb)

        self.core.emulate_frame()

        self.assertEqual(self.scanline_count, 144)

    def test_vblank_callback(self):
        """
        Test that the vblank callback is called
        """
        def cb():
            self.vblank_fired = True
        self.core.register_vblank_callback(cb)

        self.core.emulate_frame()

        self.assertTrue(self.vblank_fired)
