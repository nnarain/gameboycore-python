from unittest import TestCase

class TestAPI(TestCase):
    def setUp(self):
        from gameboycore import GameboyCore
        self.core = GameboyCore()

    def test_register_vblank_callback(self):
        """
        Test registering callable object to vblank callback (no throw)
        """
        def vblank_callback():
            pass
        self.core.register_vblank_callback(vblank_callback)

    def test_register_vblank_callback_throws(self):
        """
        Test registering non-callback object to vblank callback (throws)
        """
        vblank_callback = 0
        with self.assertRaises(RuntimeError) as ctx:
            self.core.register_vblank_callback(vblank_callback)

    def test_register_scanline_callback(self):
        """
        Test registering callback object to scanline callback
        """
        def scanline_callback(scanline, line_num):
            pass
        self.core.register_scanline_callback(scanline_callback)

    def test_register_scanline_callback_throws(self):
        """
        Test registering non-callback object to scanline callback (throws)
        """
        scanline_callback = 0
        with self.assertRaises(RuntimeError) as ctx:
            self.core.register_scanline_callback(scanline_callback)

    def test_register_audio_callback(self):
        """
        Test registering callable to audio callback
        """
        def audio_callback(s1, s2):
            pass
        self.core.register_audio_callback(audio_callback)

    def test_register_audio_callback_throws(self):
        """
        Test registering non-callback object to audio callback (throws)
        """
        audio_callback = 0
        with self.assertRaises(RuntimeError) as ctx:
            self.core.register_audio_callback(audio_callback)
