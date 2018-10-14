import unittest


class TestBasicUsage(unittest.TestCase):
    """
    Test basic usage of the module
    """

    def test_import(self):
        """
        Test importing the gameboycore module
        """
        import gameboycore

    def test_open(self):
        """
        Test opening a Gameboy ROM file
        """
        from gameboycore import GameboyCore
        core = GameboyCore()
        core.open('roms/cpu_instrs.gb')