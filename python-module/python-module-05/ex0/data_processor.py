
import typing
import abc


class DataProcessor(abc.ABC):
    def __init__(self):
        self.data = []
        self.rank = 0

    @abc.abstractmethod
    def validate(self, data: typing.Any) -> bool:
        pass

    @abc.abstractmethod
    def ingest(self, data: typing.Any) -> None:
        pass

    def output(self) -> tuple[int, str]:
        return self.data.pop(0)


class NumericProcessor(DataProcessor):
    def validate(self, data: typing.Any) -> bool:
        if isinstance(data, (int, float)):
            return True
        if isinstance(data, list):
            return all(type(item) in (int, float) for item in data)
        return False

    def ingest(self, data: typing.Union[int, float, typing.List[typing.Union[int, float]]]) -> None:
        if not self.validate(data):
            raise ValueError("Improper numeric data")

        if not isinstance(data, list):
            data = [data]

        for item in data:
            self.data.append((self.rank, str(item)))
            self.rank += 1


class TextProcessor(DataProcessor):
    def validate(self, data: typing.Any) -> bool:
        if isinstance(data, str):
            return True
        if isinstance(data, list):
            return all(isinstance(item, str) for item in data)
        return False

    def ingest(self, data: typing.Union[str, typing.List[str]]) -> None:
        if not self.validate(data):
            raise ValueError("Improper text data")

        if isinstance(data, str):
            data = [data]

        for item in data:
            self.data.append((self.rank, item))
            self.rank += 1


class LogProcessor(DataProcessor):
    def validate(self, data: typing.Any) -> bool:
        if isinstance(data, dict):
            return all(
                isinstance(key, str) and isinstance(value, str)
                for key, value in data.items()
            ) and "log_level" in data and "log_message" in data

        if isinstance(data, list):
            return all(
                self.validate(item) for item in data
            )

        return False

    def ingest(self, data: typing.Union[typing.Dict[str, str], typing.List[typing.Dict[str, str]]]) -> None:
        if not self.validate(data):
            raise ValueError("Improper log data")

        if isinstance(data, dict):
            data = [data]

        for item in data:
            result = f"{item['log_level']}: {item['log_message']}"
            self.data.append((self.rank, result))
            self.rank += 1


if __name__ == "__main__":
    print("=== Code Nexus - Data Processor ===")

    print("Testing Numeric Processor...")
    numeric = NumericProcessor()
    print(f" Trying to validate input '42' : {numeric.validate(42)}")
    print(f" Trying to validate input 'Hello' : {numeric.validate('Hello')}")
    print(" Test invalid ingestion of string 'foo' without prior validation:")
    print(f" Trying to validate input 'foo' :")
    try:
        numeric.ingest("foo")
    except ValueError as e:
        print(f" Got exception: {e}")
    print(" Processing data: [1, 2, 3, 4, 5]")
    numeric.ingest([1, 2, 3, 4, 5])
    print(" Extracting 3 values...")
    for i in range(3):
        print(f" Numeric value {i}: {numeric.output()[1]}")
    print("")
    print("Testing Text Processor...")
    text = TextProcessor()
    print(f" Trying to validate input '42' : {text.validate(42)}")
    print(" Processing data: ['Hello', 'Nexus', 'World']")
    text.ingest(["Hello", "Nexus", "World"])
    print(" Extracting3 values...")
    print(f" Text value {0}: {text.output()[1]}")
    print("")
    print("Testing Log Processor...")
    log = LogProcessor()
    print(f" Trying to validate input 'Hello' : {log.validate('Hello')}")
    print(" Processing data: [{'log_level': 'NOTICE', 'log_message': 'Connection to server'}, {'log_level': 'ERROR', 'log_message': 'Unauthorized access!!'}]")
    log.ingest([
        {"log_level": "NOTICE", "log_message": "Connection to server"},
        {"log_level": "ERROR", "log_message": "Unauthorized access!!"}
    ])
    print(" Extracting 2 values...")
    print(f" Log entry {0}: {log.output()[1]}")
    print(f" Log entry {1}: {log.output()[1]}")
