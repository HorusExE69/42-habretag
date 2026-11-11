
import typing
import abc

class DataProcessor(abc.ABC):
    def __init__(self):
        self.data = []
        self.rank = 0
        self.total_processed = 0

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
            self.total_processed += 1


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
            self.total_processed += 1


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
            self.total_processed += 1


class ExportPlugin(typing.Protocol):
    def process_output(self, data: list[tuple[int, str]]) -> None:
        ...

class CSVPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        print("CSV Output:")
        print(",".join(item[1] for item in data))

class JSONPlugin:
    def process_output(self, data: list[tuple[int, str]]) -> None:
        result = []

        for rank, value in data:
            value = value.replace("\\", "\\\\")
            value = value.replace('"', '\\"')
            value = value.replace("\n", "\\n")
            value = value.replace("\r", "\\r")
            value = value.replace("\t", "\\t")
            result.append(f'item_{rank}": "{value}"')
        print("JSON Output:")
        print("{" + ", ".join(result) + "}")

class DataStream:
    def __init__(self):
        self.processors = []

    def register_processor(self, proc: DataProcessor) -> None:
        self.processors.append(proc)

    def process_stream(self, stream: list[typing.Any]) -> None:
        for element in stream:
            processed = False

            for proc in self.processors:
                if proc.validate(element):
                    proc.ingest(element)
                    processed = True
                    break

            if not processed:
                print(
                    f"DataStream error - Can't process element in stream: {element}")

    def print_processors_stats(self) -> None:
        print("== DataStream statistics ==")

        if not self.processors:
            print("No processor found, no data")
            return

        for proc in self.processors:
            print(
                f"{proc.__class__.__name__.replace('Processor', ' Processor')}: "
                f"total {proc.total_processed} items processed, "
                f"remaining {len(proc.data)} on processor"
            )

    def output_pipeline(self, nb: int, plugin: ExportPlugin) -> None:
        for proc in self.processors:
            output = []

            for i in range(nb):
                if not proc.data:
                    break
                output.append(proc.output())

            if output:
                plugin.process_output(output)


if __name__ == "__main__":
    print("=== Code Nexus - Data Pipeline ===")

    print("")

    stream = DataStream()
    print("Initialize Data Stream...")

    print("")

    stream.print_processors_stats()

    print("")

    numeric = NumericProcessor()
    text = TextProcessor()
    log = LogProcessor()

    print("Registering Processors")
    stream.register_processor(numeric)
    stream.register_processor(text)
    stream.register_processor(log)

    print("")

    batch = [
        "Hello world",
        [3.14, -1, 2.71],
        [
            {"log_level": "WARNING", "log_message": "Telnet access! Use ssh instead"},
            {"log_level": "INFO", "log_message": "User connected"}
        ],
        42,
        ["Hi", "five"]
    ]

    print("Send first batch of data on stream:", batch)
    stream.process_stream(batch)

    print("")

    stream.print_processors_stats()

    print("")

    csv = CSVPlugin()
    print("Send 3 processed data from each processor to a CSV plugin:")
    stream.output_pipeline(3, csv)

    print("")

    stream.print_processors_stats()

    batch2 = [
        21,
        ["I love AI", "LLMs are wonderful", "Stay healthy"],
        [
            {"log_level": "ERROR", "log_message": "500 server crash"},
            {"log_level": "NOTICE", "log_message": "Certificate expires in 10 days"}
        ],
        [32, 42, 64, 84, 128, 168],
        "World hello"
    ]

    print("")

    print("Send another batch of data:", batch2)
    stream.process_stream(batch2)

    print("")

    stream.print_processors_stats()

    print("")

    json = JSONPlugin()
    print("Send 5 processed data from each processor to a JSON plugin:")
    stream.output_pipeline(5, json)

    print("")
    
    stream.print_processors_stats()
